#pragma once
#include "I2C.h"
#include <Wire.h>

// Default 7 bit MCP23017 I2C Register Address
#define MCP23017_12C_ADDRESS 0x20

class MCP23017 : public I2C
{
	public:
		MCP23017 () : I2C(MCP23017_12C_ADDRESS) {}
		MCP23017 (uint8_t i2c_address) : I2C(i2c_address) {}

		bool begin ();
		bool digitalRead (uint8_t pin);
		uint8_t digitalReadAll ();
};
