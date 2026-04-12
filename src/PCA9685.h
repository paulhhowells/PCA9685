#pragma once
#include <Wire.h>

#ifndef PCA9685_H
#define PCA9685_H

class PCA9685
{
  private:
	uint8_t _i2c_address;
	void setOpenDrainOutputMode ();
	void writeRegister (uint8_t reg, uint8_t value);

  public:
	PCA9685 ();
	PCA9685 (uint8_t i2c_address);

	bool begin ();
};

// The PCA9685 datasheet expects to be driving LEDs and names its registers accordingly.
const uint8_t PCA9685_LED_0_ON_L = 0x06;  // LED0 on mark, low byte 8 LSBs
const uint8_t PCA9685_LED_0_ON_H = 0x07;  // LED0 on mark, high byte 4 MSBs
const uint8_t PCA9685_LED_0_OFF_L = 0x08; // LED0 off mark, low byte
const uint8_t PCA9685_LED_0_OFF_H = 0x09; // LED0 off mark, high byte

const uint8_t PCA9685_LED_1_ON_L = 0x0A;
const uint8_t PCA9685_LED_1_ON_H = 0x0B;
const uint8_t PCA9685_LED_1_OFF_L = 0x0C;
const uint8_t PCA9685_LED_1_OFF_H = 0x0D;

const uint8_t PCA9685_LED_2_ON_L = 0x0E;
const uint8_t PCA9685_LED_2_ON_H = 0x0F;
const uint8_t PCA9685_LED_2_OFF_L = 0x10;
const uint8_t PCA9685_LED_2_OFF_H = 0x11;

const uint8_t PCA9685_LED_3_ON_L = 0x12;
const uint8_t PCA9685_LED_3_ON_H = 0x13;
const uint8_t PCA9685_LED_3_OFF_L = 0x14;
const uint8_t PCA9685_LED_3_OFF_H = 0x15;

const uint8_t PCA9685_LED_4_ON_L = 0x16;
const uint8_t PCA9685_LED_4_ON_H = 0x17;
const uint8_t PCA9685_LED_4_OFF_L = 0x18;
const uint8_t PCA9685_LED_4_OFF_H = 0x19;

const uint8_t PCA9685_LED_5_ON_L = 0x1A;
const uint8_t PCA9685_LED_5_ON_H = 0x1B;
const uint8_t PCA9685_LED_5_OFF_L = 0x1C;
const uint8_t PCA9685_LED_5_OFF_H = 0x1D;

const uint8_t PCA9685_LED_6_ON_L = 0x1E;
const uint8_t PCA9685_LED_6_ON_H = 0x1F;
const uint8_t PCA9685_LED_6_OFF_L = 0x20;
const uint8_t PCA9685_LED_6_OFF_H = 0x21;

const uint8_t PCA9685_LED_7_ON_L = 0x22;
const uint8_t PCA9685_LED_7_ON_H = 0x23;
const uint8_t PCA9685_LED_7_OFF_L = 0x24;
const uint8_t PCA9685_LED_7_OFF_H = 0x25;

const uint8_t PCA9685_LED_8_ON_L = 0x26;
const uint8_t PCA9685_LED_8_ON_H = 0x27;
const uint8_t PCA9685_LED_8_OFF_L = 0x28;
const uint8_t PCA9685_LED_8_OFF_H = 0x29;

const uint8_t PCA9685_LED_9_ON_L = 0x2A;
const uint8_t PCA9685_LED_9_ON_H = 0x2B;
const uint8_t PCA9685_LED_9_OFF_L = 0x2C;
const uint8_t PCA9685_LED_9_OFF_H = 0x2D;

const uint8_t PCA9685_LED_10_ON_L = 0x2E;
const uint8_t PCA9685_LED_10_ON_H = 0x2F;
const uint8_t PCA9685_LED_10_OFF_L = 0x30;
const uint8_t PCA9685_LED_10_OFF_H = 0x31;

const uint8_t PCA9685_LED_11_ON_L = 0x32;
const uint8_t PCA9685_LED_11_ON_H = 0x33;
const uint8_t PCA9685_LED_11_OFF_L = 0x34;
const uint8_t PCA9685_LED_11_OFF_H = 0x35;

const uint8_t PCA9685_LED_12_ON_L = 0x36;
const uint8_t PCA9685_LED_12_ON_H = 0x37;
const uint8_t PCA9685_LED_12_OFF_L = 0x38;
const uint8_t PCA9685_LED_12_OFF_H = 0x39;

const uint8_t PCA9685_LED_13_ON_L = 0x3A;
const uint8_t PCA9685_LED_13_ON_H = 0x3B;
const uint8_t PCA9685_LED_13_OFF_L = 0x3C;
const uint8_t PCA9685_LED_13_OFF_H = 0x3D;

const uint8_t PCA9685_LED_14_ON_L = 0x3E;
const uint8_t PCA9685_LED_14_ON_H = 0x3F;
const uint8_t PCA9685_LED_14_OFF_L = 0x40;
const uint8_t PCA9685_LED_14_OFF_H = 0x41;

const uint8_t PCA9685_LED_15_ON_L = 0x42;
const uint8_t PCA9685_LED_15_ON_H = 0x43;
const uint8_t PCA9685_LED_15_OFF_L = 0x44;
const uint8_t PCA9685_LED_15_OFF_H = 0x45;

#endif
