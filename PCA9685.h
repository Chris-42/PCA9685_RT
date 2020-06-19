#pragma once
//
//    FILE: PCA9685.H
//  AUTHOR: Rob Tillaart
//    DATE: 24-apr-2016
// VERSION: 0.2.1
// PURPOSE: Arduino library for I2C PCA9685 16 channel PWM 
//     URL: https://github.com/RobTillaart/PCA9685_RT
//
// HISTORY:
// see PCA9685.cpp file
//

#include "Arduino.h"

#define PCA9685_LIB_VERSION "0.2.1"

// ERROR CODES
#define PCA9685_OK          0x00
#define PCA9685_ERROR       0xFF
#define PCA9685_ERR_CHANNEL 0xFE
#define PCA9685_ERR_MODE    0xFD
#define PCA9685_ERR_I2C     0xFC


class PCA9685
{
public:
  explicit PCA9685(const uint8_t deviceAddress);

#if defined (ESP8266) || defined(ESP32)
  void    begin(uint8_t sda, uint8_t scl);
#endif
  void    begin();
  void    reset();

  // reg = 1, 2  check datasheet for values
  void    writeMode(uint8_t reg, uint8_t value);
  uint8_t readMode(uint8_t reg);

  // single PWM setting, channel = 0..15,
  // onTime = 0..4095, offTime = 0..4095
  // allows shifted PWM's e.g. 2 servo's that do not start at same time.
  void    setPWM(uint8_t channel, uint16_t onTime, uint16_t offTime);
  void    getPWM(uint8_t channel, uint16_t* onTime, uint16_t* offTime);

  // single PWM setting, channel = 0..15, offTime = 0..4095  (onTime = 0)
  void    setPWM(uint8_t channel, uint16_t offTime);

  // set update frequency for all channels
  // freq = 24 - 1526 Hz
  void    setFrequency(uint16_t freq);

  // set channel  HIGH or LOW (effectively no PWM)
  void    digitalWrite(uint8_t channel, uint8_t mode);

  // for backwards compatibility; will be removed in future
  void    setON(uint8_t channel)   { digitalWrite(channel, HIGH); };
  void    setOFF(uint8_t channel)  { digitalWrite(channel, LOW); };

  int     lastError();

private:
  
  // DIRECT CONTROL
  void    writeReg(uint8_t reg, uint8_t value);
  void    writeReg2(uint8_t reg, uint16_t a, uint16_t b);
  uint8_t readReg(uint8_t reg);

  uint8_t _address;
  int     _error;
};

// -- END OF FILE --
