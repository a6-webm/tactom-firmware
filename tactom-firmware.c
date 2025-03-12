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

#define I2C_SDA 0
#define I2C_SCL 1
#define BAUD (400 * 1000)

/*
Placement of drivers on the palm-side of the forearm:
Numbers represent the index of the driver
  Palm
  0  1  2
  3  4  5
  6  7  8
  9 10 11
  Elbow
*/
#define NUM_DRVS 2
const u8 DRV_ADDRESSES[NUM_DRVS] = {0x70, 0x70};
const u8 DRV_PORTS[NUM_DRVS] = {0, 1};
// #define NUM_DRVS 12
// const u8 DRV_ADDRESSES[NUM_DRVS] = {
//     0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71,
// };
// const u8 DRV_PORTS[NUM_DRVS] = {0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5};

void flash(u8 flashes) {
  for (u8 i = 0; i < flashes; i++) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(60);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(120);
  }
}

inline void play_ev(Ev ev, Drv2605 *drvs) {
  if (ev.ev_type == END_GLYPH)
    return;
  drv2605_go(drvs[ev.ev_type]);
}

void queue_glyph_from_get_char(void *eb) {
  printf("huh\n");
  char c = getchar_timeout_us(0);
  queue_glyph_events(eb, c);
}

int main() {
  stdio_init_all();
  // WARN DBG wait for terminal to connect
  while (!tud_cdc_connected()) {
    sleep_ms(100);
  }

  if (cyw43_arch_init()) {
    printf("Wi-Fi init failed\n");
    return -1;
  }

  if (i2c_init(i2c_default, BAUD) != BAUD) {
    return -1;
  }
  gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA);
  gpio_pull_up(I2C_SCL);

  Drv2605 drvs[NUM_DRVS];
  for (int i = 0; i < NUM_DRVS; i++) {
    drvs[i] = drv2605(DRV_ADDRESSES[i], DRV_PORTS[i]);
  }

  flash(2);
  printf("finished setup, initialising drivers\n");

  for (int i = 0; i < NUM_DRVS; i++) {
    while (drv2605_init_for_hd_la0503_lw28_motor(drvs[i]) < 0) {
      printf("ERR: error initialising drv: %d\n", i);
    }
    printf("initialised drv: %d\n", i);
  }

  printf("drives initialised\n");
  stdio_flush();

  EvBuf eb;

  stdio_set_chars_available_callback(queue_glyph_from_get_char, &eb);

  while (true) {
    if (!eb_is_empty(&eb)) {
      // TODO write some code that drains and just prints the ev queue so u can
      // tell what's going on
      Ev ev = eb_peek(&eb);
      if (ev.abs_time <= get_absolute_time()) {
        play_ev(ev, drvs);
        eb_pop(&eb);
      }
    }
  }
}
