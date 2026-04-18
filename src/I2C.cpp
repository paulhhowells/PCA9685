#include "I2C.h"

uint8_t I2C::readRegister (uint8_t reg)
{
	Wire.beginTransmission(_i2c_address);
	Wire.write(reg);
	Wire.endTransmission();

	uint8_t request_quantity = 1;
	Wire.requestFrom(_i2c_address, request_quantity);

	return Wire.read();
}

void I2C::writeRegister (uint8_t reg, uint8_t value)
{
	Wire.beginTransmission(_i2c_address);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}
