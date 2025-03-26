#include "drv2605.h"
#include <math.h>
#include <pico/time.h>
#include <stdio.h>

Drv2605 drv2605(i2c_inst_t *i2c, u8 port) {
  Drv2605 drv;
  drv.i2c = i2c;
  drv.port = port;
  return drv;
}

void select_port(Drv2605 drv) {
  u8 mult_mask = 1 << drv.port;
  i2c_write_blocking(drv.i2c, MULT_ADDR, &mult_mask, 1, false);
}

void write_reg(Drv2605 drv, u8 reg, u8 val) {
  u8 buffer[2] = {reg, val};
  i2c_write_blocking(drv.i2c, DRV2605_ADDR, buffer, 2, false);
}

// TODO error handling
void drv2605_write_reg(Drv2605 drv, u8 reg, u8 val) {
  select_port(drv);
  write_reg(drv, reg, val);
}

u8 read_reg(Drv2605 drv, u8 reg) {
  i2c_write_blocking(drv.i2c, DRV2605_ADDR, &reg, 1, true);
  u8 buffer;
  i2c_read_blocking(drv.i2c, DRV2605_ADDR, &buffer, 1, false);
  return buffer;
}

// TODO error handling
u8 drv2605_read_reg(Drv2605 drv, u8 reg) {
  select_port(drv);
  return read_reg(drv, reg);
}

void set_part_of_reg(Drv2605 drv, u8 reg, u8 mask, u8 val) {
  write_reg(drv, reg, read_reg(drv, reg) & mask | val);
}

void drv2605_go(Drv2605 drv) { drv2605_write_reg(drv, DRV2605_REG_GO, 1); }

void set_wave(Drv2605 drv, u8 wave) {
  write_reg(drv, DRV2605_REG_WAVESEQ1, wave);
  write_reg(drv, DRV2605_REG_WAVESEQ2, 0); // end sequence
}

void drv2605_set_wave(Drv2605 drv, u8 wave) {
  select_port(drv);
  set_wave(drv, wave);
}

int init(Drv2605 drv, float rated_v, float clamp_v, float frequency,
         bool calibrate, u8 bemf_gain, u8 a_cal_comp, u8 a_cal_bemf,
         bool open_loop) {

  set_part_of_reg(drv, DRV2605_REG_FEEDBACK, 0b01111111, 1 << 7); // LRA mode

  float s_t = 300 * 0.000001; // default sample time: 300us
  write_reg(drv, DRV2605_REG_RATEDV,
            (u8)(rated_v * sqrt(1 - (4 * s_t + 300 * 0.000001) * frequency) /
                 (20.71 * 0.001)));

  if (open_loop) {
    set_part_of_reg(drv, DRV2605_REG_CONTROL3, 0b11111110,
                    1); // LRA_OPEN_LOOP
    write_reg(
        drv, DRV2605_REG_CLAMPV,
        (u8)(rated_v / (21.33 * 0.001 * sqrt(1 - frequency * 800 * 0.000001))));
  } else {
    write_reg(drv, DRV2605_REG_CLAMPV, (u8)(clamp_v / (21.96 * 0.001)));
  }

  set_part_of_reg(drv, DRV2605_REG_CONTROL1, 0b11110000,
                  (u8)((0.5 * 1000 * 1 / frequency - 0.5) / 0.1)); // DRIVE_TIME

  if (calibrate) {
    write_reg(drv, DRV2605_REG_MODE, 0x07); // auto-calibrate mode

    write_reg(drv, DRV2605_REG_GO, 1); // start calibration

    while (read_reg(drv, DRV2605_REG_GO) != 0) {
      sleep_ms(100);
    }

    // if DIAG_RESULT == 1, error
    if ((read_reg(drv, DRV2605_REG_STATUS) >> 3) & 1) {
      return -1;
    }

    printf("auto calibrate results:\n");
    u8 bemf_gain = read_reg(drv, DRV2605_REG_FEEDBACK) & 0b00000011;
    u8 a_cal_comp = read_reg(drv, DRV2605_REG_AUTOCALCOMP);
    u8 a_cal_bemf = read_reg(drv, DRV2605_REG_AUTOCALEMF);
    int actual_gain = bemf_gain == 0 ? 5 : bemf_gain * 10;
    printf("bemf_gain: %i -> %ix\n", bemf_gain, actual_gain);
    printf("a_cal_comp: %i -> %f\n", a_cal_comp, 1 + a_cal_comp / 255.0);
    printf("a_cal_bemf: %i -> %fV\n", a_cal_bemf,
           (a_cal_bemf / 255.0) * 1.22 / bemf_gain);
  } else {
    set_part_of_reg(drv, DRV2605_REG_FEEDBACK, 0b11111100, bemf_gain);
    write_reg(drv, DRV2605_REG_AUTOCALCOMP, a_cal_comp);
    write_reg(drv, DRV2605_REG_AUTOCALEMF, a_cal_bemf);
  }
  write_reg(drv, DRV2605_REG_MODE, DRV2605_MODE_INTTRIG);

  set_part_of_reg(drv, DRV2605_REG_LIBRARY, 0b11111000,
                  6);        // LRA effect library
  drv2605_set_wave(drv, 24); // Sharp tick
  return 0;
}

void drv2605_init(Drv2605 drv, float rated_v, float clamp_v, float frequency,
                  u8 bemf_gain, u8 a_cal_comp, u8 a_cal_bemf, bool open_loop) {
  select_port(drv);
  init(drv, rated_v, clamp_v, frequency, false, bemf_gain, a_cal_comp,
       a_cal_bemf, false);
}

/// Returns:
/// 0: no error
/// -1: auto-calibration failed
int drv2605_init_auto_calib(Drv2605 drv, float rated_v, float clamp_v,
                            float frequency, bool open_loop) {
  select_port(drv);
  return init(drv, rated_v, clamp_v, frequency, true, 0, 0, 0, false);
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
