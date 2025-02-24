#include "drv2605.h"
#include <hardware/i2c.h>

Drv2605 drv2605(i2c_inst_t *i2c_inst, u8 addr) {
  Drv2605 drv;
  drv.i2c_inst = i2c_inst;
  drv.addr = addr;
  return drv;
}

// TODO error handling
void drv2605_write_reg(Drv2605 drv, u8 reg, u8 val) {
  u8 buffer[2] = {reg, val};
  i2c_write_blocking(drv.i2c_inst, drv.addr, buffer, 2, false);
}

// TODO error handling
u8 drv2605_read_reg(Drv2605 drv, u8 reg) {
  u8 buffer;
  // TODO why do we write then read and does this work lol?
  i2c_write_blocking(drv.i2c_inst, drv.addr, &buffer, 1, false);
  i2c_read_blocking(drv.i2c_inst, drv.addr, &buffer, 1, false);
  return buffer;
}

void drv2605_init_for_hd_la0503_lw28_motor(Drv2605 drv) {
  // TODO auto calibration
  // auto-calibration ---------------------------------------------------------
  drv2605_write_reg(drv, DRV2605_REG_MODE, 0x07); // auto-calibrate mode

  u8 fb = 1 << 7   // LRA mode
          & 3 << 4 // default fb_brake_factor: 4x
          & 1 << 2 // default loop_gain: medium
      ;
  drv2605_write_reg(drv, DRV2605_REG_FEEDBACK, fb);

  // TODO are we sure the driver is in "closed-loop mode"?
  // seems to be in the Control3 register, not sure when we set that

  // TODO figure out if 26 (0.689Vrms) or 27 (0.716Vrms) is better
  drv2605_write_reg(drv, DRV2605_REG_RATEDV, 26);

  // TODO pick this number not based off vibes (1.21V)
  drv2605_write_reg(drv, DRV2605_REG_CLAMPV, 55);

  drv2605_write_reg(drv, DRV2605_REG_RTPIN,
                    0x00); // no real-time-playback
  // --------------------------------------------------------------------------

  // TODO what does this do
  drv2605_write_reg(drv, DRV2605_REG_WAVESEQ1, 1); // strong click
  drv2605_write_reg(drv, DRV2605_REG_WAVESEQ2, 0); // end sequence

  // write_register(drv2605_inst, DRV2605_REG_OVERDRIVE, 0); // no overdrive

  drv2605_write_reg(drv, DRV2605_REG_SUSTAINPOS, 0);
  drv2605_write_reg(drv, DRV2605_REG_SUSTAINNEG, 0);
  drv2605_write_reg(drv, DRV2605_REG_BREAK, 0);
  drv2605_write_reg(drv, DRV2605_REG_AUDIOMAX, 0x64);

  // TODO change to LRA
  // ERM open loop

  // turn off N_ERM_LRA
  drv2605_write_reg(drv, DRV2605_REG_FEEDBACK,
                    drv2605_read_reg(drv, DRV2605_REG_FEEDBACK) & 0x7F);
  // turn on ERM_OPEN_LOOP
  drv2605_write_reg(drv, DRV2605_REG_CONTROL3,
                    drv2605_read_reg(drv, DRV2605_REG_CONTROL3) | 0x20);
}

/**************************************************************************/
/*!
  @brief Select the haptic waveform to use.
  @param slot The waveform slot to set, from 0 to 7
  @param w The waveform sequence value, refers to an index in the ROM library.

    Playback starts at slot 0 and continues through to slot 7, stopping if it
  encounters a value of 0. A list of available waveforms can be found in
  section 11.2 of the datasheet: http://www.adafruit.com/datasheets/DRV2605.pdf
*/
/**************************************************************************/
// void Adafruit_DRV2605::setWaveform(uint8_t slot, uint8_t w) {
//   writeRegister8(DRV2605_REG_WAVESEQ1 + slot, w);
// }

/**************************************************************************/
/*!
  @brief Select the waveform library to use.
  @param lib Library to use, 0 = Empty, 1-5 are ERM, 6 is LRA.

    See section 7.6.4 in the datasheet for more details:
  http://www.adafruit.com/datasheets/DRV2605.pdf
*/
/**************************************************************************/
// void Adafruit_DRV2605::selectLibrary(uint8_t lib) {
//   writeRegister8(DRV2605_REG_LIBRARY, lib);
// }

/**************************************************************************/
/*!
  @brief Start playback of the waveforms (start moving!).
*/
/**************************************************************************/
// void Adafruit_DRV2605::go() { writeRegister8(DRV2605_REG_GO, 1); }

/**************************************************************************/
/*!
  @brief Stop playback.
*/
/**************************************************************************/
// void Adafruit_DRV2605::stop() { writeRegister8(DRV2605_REG_GO, 0); }

/**************************************************************************/
/*!
  @brief Set the device mode.
  @param mode Mode value, see datasheet section 7.6.2:
  http://www.adafruit.com/datasheets/DRV2605.pdf

    0: Internal trigger, call go() to start playback\n
    1: External trigger, rising edge on IN pin starts playback\n
    2: External trigger, playback follows the state of IN pin\n
    3: PWM/analog input\n
    4: Audio\n
    5: Real-time playback\n
    6: Diagnostics\n
    7: Auto calibration
*/
/**************************************************************************/
// void Adafruit_DRV2605::setMode(uint8_t mode) {
//   writeRegister8(DRV2605_REG_MODE, mode);
// }

/**************************************************************************/
/*!
  @brief Set the realtime value when in RTP mode, used to directly drive the
  haptic motor.
  @param rtp 8-bit drive value.
*/
/**************************************************************************/
// void Adafruit_DRV2605::setRealtimeValue(uint8_t rtp) {
//   writeRegister8(DRV2605_REG_RTPIN, rtp);
// }

/**************************************************************************/
/*!
  @brief Use ERM (Eccentric Rotating Mass) mode.
*/
/**************************************************************************/
// void Adafruit_DRV2605::useERM() {
//   writeRegister8(DRV2605_REG_FEEDBACK,
//                  readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
// }

/**************************************************************************/
/*!
  @brief Use LRA (Linear Resonance Actuator) mode.
*/
/**************************************************************************/
// void Adafruit_DRV2605::useLRA() {
//   writeRegister8(DRV2605_REG_FEEDBACK,
//                  readRegister8(DRV2605_REG_FEEDBACK) | 0x80);
// }

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
