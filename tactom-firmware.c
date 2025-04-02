#include "drv2605.h"
#include "event.h"
#include "glyphs.h"
#include "pico/cyw43_arch.h"
#include "pico/stdio.h"
#include "tusb.h"
#include <hardware/i2c.h>
#include <pico/error.h>
#include <pico/stdio.h>
#include <pico/time.h>
#include <stdio.h>
#include <stdlib.h>

#define I2C0_SDA 0
#define I2C0_SCL 1
#define I2C1_SDA 2
#define I2C1_SCL 3
#define BAUD (400 * 1000)
#define INPUT_BUFFER_SIZE 1000

#define RAW_ENTER 0xC0
#define RAW_EXIT 0xF5

typedef unsigned short u16;

/*
Placement of motors on the palm, with the plam facing the table:
Numbers represent the index of the motor
  Fingers
  0  1  2  3
  4  5  6  7
  8  9 10 11
  Wrist
*/

#define NUM_DRVS 12
const Drv2605 DRVS[NUM_DRVS] = {
    {.i2c = i2c0, .port = 3}, // 0
    {.i2c = i2c0, .port = 2}, // 1
    {.i2c = i2c0, .port = 4}, // 2
    {.i2c = i2c0, .port = 5}, // 3
    {.i2c = i2c1, .port = 5}, // 4
    {.i2c = i2c1, .port = 4}, // 5
    {.i2c = i2c0, .port = 0}, // 6
    {.i2c = i2c0, .port = 1}, // 7
    {.i2c = i2c1, .port = 2}, // 8
    {.i2c = i2c1, .port = 1}, // 9
    {.i2c = i2c1, .port = 3}, // 10
    {.i2c = i2c1, .port = 0}, // 11
};

void flash(u8 flashes, uint delta) {
  for (u8 i = 0; i < flashes; i++) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(delta);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(delta * 2);
  }
}

void play_ev(Ev ev, Drv2605 const *drvs) {
  if (ev.ev_type == END_GLYPH)
    return;
  drv2605_go(drvs[ev.ev_type]);
}

typedef struct stdin_callback_data {
  char *buf;
  size_t buf_len;
  EvBuf *ev_buf;
  bool raw;
} stdin_callback_data;

void add_inp_buf(stdin_callback_data *data, char c) {
  if (data->buf_len != INPUT_BUFFER_SIZE) { // add character
    data->buf[data->buf_len] = c;
    data->buf[data->buf_len + 1] = '\0';
    data->buf_len++;
  }
}

void del_inp_buf(stdin_callback_data *data) {
  data->buf_len--;
  data->buf[data->buf_len] = '\0';
}

void queue_inp_buf(stdin_callback_data *data) {
  if (data->raw) {
    absolute_time_t last_time = eb_last_timestamp(data->ev_buf);
    for (size_t i = 0; i < data->buf_len; i += 3) {
      union {
        u8 bytes[2];
        u16 ms;
      } time = {.bytes = {data->buf[i + 2], data->buf[i + 1]}};
      Ev ev = {.ev_type = data->buf[i + 0], .abs_time = MS(time.ms)};
      queue_event(data->ev_buf, ev, last_time);
    }
  } else {
    data->buf[data->buf_len] = '\0';
    for (size_t i = 0; i < data->buf_len; i++) {
      queue_glyph_events(data->ev_buf, data->buf[i]);
    }
    printf("'%s' queued\n", data->buf);
  }
  data->buf_len = 0;
  data->buf[0] = '\0';
}

void handle_stdin_char(void *callback_data) {
  stdin_callback_data *data = callback_data;
  char c = getchar_timeout_us(0);
  if (c == RAW_ENTER) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    data->buf_len = 0;
    data->raw = true;
    return;
  }
  if (c == RAW_EXIT && data->buf_len % 3 == 0) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    queue_inp_buf(data);
    data->raw = false;
    return;
  }
  if (data->raw) {
    add_inp_buf(data, c);
    return;
  }
  if (c == '\r') {
    queue_inp_buf(data);
    return;
  }
  if (c == 127 && data->buf_len != 0) { // backspace
    del_inp_buf(data);
    printf("msg: %s\n", data->buf);
    return;
  }
  add_inp_buf(data, c);
  printf("msg: %s\n", data->buf);
}

int main() {
  stdio_init_all();
  // WARN waits for terminal to connect
  // while (!tud_cdc_connected()) {
  //   sleep_ms(100);
  // }

  if (cyw43_arch_init()) {
    printf("Wi-Fi init failed\n");
    return -1;
  }

  if (i2c_init(i2c0, BAUD) != BAUD) {
    printf("ERR: i2c init failed\n");
    return -1;
  }
  if (i2c_init(i2c1, BAUD) != BAUD) {
    printf("ERR: i2c init failed\n");
    return -1;
  }
  gpio_set_function(I2C0_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C0_SCL, GPIO_FUNC_I2C);
  gpio_set_function(I2C1_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C1_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C0_SDA);
  gpio_pull_up(I2C0_SCL);
  gpio_pull_up(I2C1_SDA);
  gpio_pull_up(I2C1_SCL);

  flash(2, 60);
  printf("finished setup, initialising drivers\n");

  // TODO pick clamp_v not off vibes
  for (int i = 0; i < NUM_DRVS; i++) {
    // params for an HD-LA0503-LW28 motor
    // while (drv2605_init_auto_calib(DRVS[i], 0.7, 1.2, 260, false) < 0) {
    //   printf("ERR: error initialising driver, retrying...\n");
    // }
    // params for an HD-LA0503-LW28 motor on sponge with some pressure applied
    drv2605_init(DRVS[i], 0.7, 1.2, 260, 3, 13, 80, false);
    printf("initialised drv: %d\n", i);
    // flash(1);
  }

  printf("drives initialised\n");
  flash(3, 60);
  stdio_flush();

  EvBuf eb = ev_buf();
  stdin_callback_data callback_data = {
      .ev_buf = &eb,
      .buf = malloc(sizeof(char) * INPUT_BUFFER_SIZE),
      .buf_len = 0};

  stdio_set_chars_available_callback(handle_stdin_char, &callback_data);

  while (true) {
    if (!eb_is_empty(&eb)) {
      Ev ev = eb_peek(&eb);
      if (ev.abs_time <= get_absolute_time()) {
        play_ev(ev, DRVS);
        printf("ev: %d\n", ev.ev_type);
        eb_pop(&eb);
      }
    }
  }

  eb_free(eb);
  free(callback_data.buf);
}
