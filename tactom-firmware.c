#include "drv2605.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "tusb.h"
#include <hardware/i2c.h>
#include <pico/error.h>
#include <pico/stdio.h>
#include <pico/time.h>
#include <stdio.h>

#define I2C_SDA 0
#define I2C_SCL 1
#define BAUD (400 * 1000)

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

  while (true) {
    for (int i = 0; i < NUM_DRVS; i++) {
      drv2605_go(drvs[i]);
    }
    flash(1);
    sleep_ms(1000);
  }
}
