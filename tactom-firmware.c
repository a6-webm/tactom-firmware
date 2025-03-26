#include "drv2605.h"
#include "event.h"
#include "glyphs.h"
#include "s_matrix.h"
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <pico/cyw43_arch.h>
#include <pico/error.h>
#include <pico/stdio.h>
#include <pico/time.h>
#include <pico/types.h>
#include <stdlib.h>
#include <tusb.h>

#define I2C_SDA 0
#define I2C_SCL 1
#define BAUD (400 * 1000)
#define INPUT_BUFFER_SIZE 1000

#define RAW_ENTER 0xC0
#define RAW_EXIT 0xC1

typedef unsigned short u16;

/*
Placement of motors on the palm:
Numbers represent the index of the motor
  Fingers
  0  1  2
  3  4  5
  6  7  8
  9 10 11
  Wrist
*/

void flash(u8 flashes) {
  for (u8 i = 0; i < flashes; i++) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(60);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(120);
  }
}

inline void play_ev(Ev ev, s_matrix *s_m) {
  if (ev.ev_type == END_GLYPH)
    return;
  s_matrix_select(s_m, ev.ev_type);
  drv2605_go();
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
    data->buf_len = 0;
    data->raw = true;
    return;
  }
  if (c == RAW_EXIT && data->buf_len % 3 == 0) {
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
  while (!tud_cdc_connected()) {
    sleep_ms(100);
  }

  if (cyw43_arch_init()) {
    printf("ERR: Wi-Fi init failed\n");
    return -1;
  }

  if (i2c_init(i2c_default, BAUD) != BAUD) {
    printf("ERR: i2c init failed\n");
    return -1;
  }

  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);

  s_matrix switch_matrix;
  s_matrix_init(&switch_matrix);

  flash(2);
  printf("finished setup, initialising driver\n");

  // TODO pick clamp_v not off vibes

  // HD-LA0503-LW28
  // while (drv2605_init_auto_calib(0.7, 1.2, 260, false) < 0) {
  // HD-LA0503-LW28 + 22 Ohms
  // while (drv2605_init_auto_calib(2.1, 3, 260, true) < 0) {
  // HD-LA0503-LW28 + 44 Ohms
  // while (drv2605_init_auto_calib(4, 4, 260, true) < 0) {
  //   printf("ERR: error initialising driver, retrying...\n");
  // }

  drv2605_init(4.4, 4.4, 260, 3, 23, 54, true);

  printf("driver initialised\n");
  flash(3);
  stdio_flush();

  EvBuf eb = ev_buf();
  stdin_callback_data callback_data = {
      .ev_buf = &eb,
      .buf = malloc(sizeof(char) * INPUT_BUFFER_SIZE),
      .buf_len = 0,
      .raw = false};

  stdio_set_chars_available_callback(handle_stdin_char, &callback_data);

  // absolute_time_t timer = get_absolute_time() + MS(1000);
  // while (true) {
  //   if (get_absolute_time() >= timer) {
  //     drv2605_go();
  //     timer = get_absolute_time() + MS(1000);
  //   }
  // }

  while (true) {
    if (!eb_is_empty(&eb)) {
      Ev ev = eb_peek(&eb);
      if (ev.abs_time <= get_absolute_time()) {
        play_ev(ev, &switch_matrix);
        printf("ev: %d\n", ev.ev_type);
        eb_pop(&eb);
      }
    }
  }

  eb_free(eb);
  free(callback_data.buf);
  s_matrix_free(switch_matrix);
}
