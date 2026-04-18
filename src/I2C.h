#pragma once
#include <Wire.h>

class I2C
{
  protected:
	uint8_t _i2c_address;

  public:
	I2C (uint8_t i2c_address) : _i2c_address(i2c_address)
	{
	}
	void writeRegister (uint8_t reg, uint8_t value);
	uint8_t readRegister (uint8_t reg);
};
