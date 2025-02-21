#include "drv2605.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include <stdio.h>

#define I2C0_SDA 1
#define I2C0_SCL 2
#define I2C1_SDA 4
#define I2C1_SCL 5
#define BAUD 400 * 1000

#define NUM_DRV 12
// I2C1_SPLIT splits the DRV_ADDRESSES array in two, so that the former
// addresses are accessed with i2c0, and the latter i2c1
#define I2C1_SPLIT 6
const u8 DRV_ADDRESSES[NUM_DRV] = {
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75,
};

int main() {
  stdio_init_all();

  // Initialise the Wi-Fi chip
  if (cyw43_arch_init()) {
    printf("Wi-Fi init failed\n");
    return -1;
  }

  // I2C Initialisation. Using it at 400Khz.
  if (i2c_init(i2c0, BAUD) != BAUD) {
    return -1;
  }
  if (i2c_init(i2c1, BAUD) != BAUD) {
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

  Drv2605 drvs[NUM_DRV];
  for (int i = 0; i < I2C1_SPLIT; i++) {
    drvs[i] = drv2605(i2c0, DRV_ADDRESSES[i]);
  }
  for (int i = I2C1_SPLIT; i < NUM_DRV; i++) {
    drvs[i] = drv2605(i2c1, DRV_ADDRESSES[i]);
  }

  // Example to turn on the Pico W LED
  // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

  for (int i = 0; i < NUM_DRV; i++) {
    drv2605_init(drvs[i]);
  }

  while (true) {
    printf("Hello, world!\n");
    sleep_ms(1000);
  }
}
