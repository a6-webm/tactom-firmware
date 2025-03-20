#include "drv2605.h"
#include "event.h"
#include "glyphs.h"
#include "pico/cyw43_arch.h"
#include "pico/stdio.h"
#include "tusb.h"
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <pico/error.h>
#include <pico/stdio.h>
#include <pico/time.h>
#include <stdio.h>
#include <stdlib.h>

#define I2C_SDA 0
#define I2C_SCL 1
#define BAUD (400 * 1000)
#define INPUT_BUFFER_SIZE 1000

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

#define NUM_MOTORS 12
const u8 MOTOR_GPIOS[NUM_MOTORS] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

u8 selected_motor;

void flash(u8 flashes) {
  for (u8 i = 0; i < flashes; i++) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(60);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(120);
  }
}

inline void play_ev(Ev ev) {
  if (ev.ev_type == END_GLYPH)
    return;
  gpio_put(MOTOR_GPIOS[selected_motor], false);
  selected_motor = ev.ev_type;
  gpio_put(MOTOR_GPIOS[selected_motor], true);
  drv2605_go();
}

typedef struct stdin_callback_data {
  char *buf;
  size_t buf_len;
  EvBuf *ev_buf;
} stdin_callback_data;

void handle_stdin_char(void *callback_data) {
  stdin_callback_data *data = callback_data;
  char c = getchar_timeout_us(0);
  if (c == '\r') {
    data->buf[data->buf_len] = '\0';
    for (size_t i = 0; i < data->buf_len; i++) {
      queue_glyph_events(data->ev_buf, data->buf[i]);
    }
    printf("'%s' queued\n", data->buf);
    data->buf_len = 0;
    return;
  }
  if (c == 127 && data->buf_len != 0) { // backspace
    data->buf_len--;
    data->buf[data->buf_len] = '\0';
    printf("msg: %s\n", data->buf);
    return;
  }
  if (data->buf_len != INPUT_BUFFER_SIZE) { // add character
    data->buf[data->buf_len] = c;
    data->buf[data->buf_len + 1] = '\0';
    data->buf_len++;
  }
  printf("msg: %s\n", data->buf);
}

int main() {
  stdio_init_all();
  // WARN waits for terminal to connect
  while (!tud_cdc_connected()) {
    sleep_ms(100);
  }

  if (cyw43_arch_init()) {
    printf("Wi-Fi init failed\n");
    return -1;
  }

  if (i2c_init(i2c0, BAUD) != BAUD) {
    return -1;
  }
  if (i2c_init(i2c1, BAUD) != BAUD) {
    return -1;
  }
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);

  for (int i = 0; i < NUM_MOTORS; i++) {
    gpio_init(MOTOR_GPIOS[i]);
    gpio_set_dir(MOTOR_GPIOS[i], true);
    gpio_put(MOTOR_GPIOS[i], false);
  }
  selected_motor = 0;
  gpio_put(MOTOR_GPIOS[selected_motor], true);
  flash(2);
  printf("finished setup, initialising driver\n");

  while (drv2605_init_for_hd_la0503_lw28_motor() < 0) {
    printf("ERR: error initialising driver, retrying...");
  }

  printf("driver initialised\n");
  flash(3);
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
        play_ev(ev);
        printf("ev: %d\n", ev.ev_type);
        eb_pop(&eb);
      }
    }
  }

  eb_free(eb);
  free(callback_data.buf);
}
