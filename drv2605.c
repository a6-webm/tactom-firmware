#include "drv2605.h"
#include <pico/time.h>

// TODO error handling
inline void drv2605_write_reg(u8 reg, u8 val) {
  u8 buffer[2] = {reg, val};
  i2c_write_blocking(i2c_default, DRV2605_ADDR, buffer, 2, false);
}

// TODO error handling
inline u8 drv2605_read_reg(u8 reg) {
  i2c_write_blocking(i2c_default, DRV2605_ADDR, &reg, 1, true);
  u8 buffer;
  i2c_read_blocking(i2c_default, DRV2605_ADDR, &buffer, 1, false);
  return buffer;
}

inline void set_part_of_reg(u8 reg, u8 mask, u8 val) {
  drv2605_write_reg(reg, drv2605_read_reg(reg) & mask | val);
}

void drv2605_go() { drv2605_write_reg(DRV2605_REG_GO, 1); }

inline void drv2605_set_wave(u8 wave) {
  drv2605_write_reg(DRV2605_REG_WAVESEQ1, wave);
  drv2605_write_reg(DRV2605_REG_WAVESEQ2, 0); // end sequence
}

/// Returns:
/// 0: no error
/// -1: auto-calibration failed
int drv2605_init_for_hd_la0503_lw28_motor() {
  // TODO store auto-calibration data and write it instead of auto-calibrating
  // TODO calibration might be unnecesarily different for each motor
  // auto-calibration ---------------------------------------------------------
  drv2605_write_reg(DRV2605_REG_MODE, 0x07); // auto-calibrate mode

  u8 fb = 1 << 7   // LRA mode
          & 3 << 4 // default fb_brake_factor: 4x
          & 1 << 2 // default loop_gain: medium
      ;
  drv2605_write_reg(DRV2605_REG_FEEDBACK, fb);

  // TODO figure out if 26 (0.689Vrms) or 27 (0.716Vrms) is better
  drv2605_write_reg(DRV2605_REG_RATEDV, 26);

  // TODO pick this number not based off vibes (1.21V)
  drv2605_write_reg(DRV2605_REG_CLAMPV, 55);

  set_part_of_reg(DRV2605_REG_CONTROL1, 0b11110000,
                  14); // DRIVE_TIME set to 1.92ms

  drv2605_write_reg(DRV2605_REG_GO, 1); // start calibration

  while (drv2605_read_reg(DRV2605_REG_GO) != 0) {
    sleep_ms(100);
  }

  // if DIAG_RESULT == 1, error
  if ((drv2605_read_reg(DRV2605_REG_STATUS) >> 3) & 1) {
    return -1;
  }
  // --------------------------------------------------------------------------

  drv2605_write_reg(DRV2605_REG_MODE, DRV2605_MODE_INTTRIG);

  set_part_of_reg(DRV2605_REG_LIBRARY, 0b11111000,
                  6);   // LRA effect library
  drv2605_set_wave(24); // Sharp tick

  return 0;
}

/**************************************************************************/
/* Portions of this project have been copied from the Adafruit DRV2605L Haptic
 * Driver library, which is under the following license */
/**************************************************************************/
/*!
 * @file Adafruit_DRV2605.cpp
 *
 * @mainpage Adafruit DRV2605L Haptic Driver
 *
 * @section intro_sec Introduction
 *
 * This is a library for the Adafruit DRV2605L Haptic Driver ---->
 * http://www.adafruit.com/products/2305
 *
 * Check out the links above for our tutorials and wiring diagrams.
 *
 * This motor/haptic driver uses I2C to communicate.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section author Author
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * @section license License
 *
 * MIT license, all text above must be included in any redistribution.
 *
 */
/**************************************************************************/
