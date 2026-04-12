#include "PCA9685.h"
// #include <Arduino.h>

// PCA9685 Register Addresses
#define PCA9685_I2C_ADDRESS 0x40 // Default 7 bit I2C address

#define PCA9685_MODE_1_REG 0x00       // Mode 1 register address
#define PCA9685_MODE_2_REG 0x01       // Mode 2 register address
#define PCA9685_MODE_2_REGOUTDRV 0x04 // Bit 2 controls output mode
#define PCA9685_PRESCALE 0xFE         // Prescaler for PWM output frequency

/**
 * @brief Default constructor for PCA9685 class.
 *
 * Initializes a new instance of the PCA9685 PWM driver controller.
 * The PCA9685 is a 16-channel, 12-bit PWM controller commonly used for
 * servo control and LED dimming applications.
 *
 * This constructor performs basic initialization. Further configuration
 * such as I2C address, frequency, and pin modes should be set up after
 * instantiation using appropriate setter methods.
 */
PCA9685::PCA9685 ()
{
	_i2c_address = PCA9685_I2C_ADDRESS;
}

PCA9685::PCA9685 (uint8_t i2c_address)
{
	_i2c_address = i2c_address;
}

bool PCA9685::begin ()
{
	setOpenDrainOutputMode();
	// setFrequency(1600); // 1600 Hz
	return true;
}

void PCA9685::setOpenDrainOutputMode ()
{
	// Set Mode 2 to open drain instead of totem pole output.

	// Configure open-drain mode
	uint8_t mode_2 = readRegister(PCA9685_MODE_2_REG);

	// Use a mask to set the OUTDRV bit to 0 for open-drain
	mode_2 &= ~PCA9685_MODE_2_REGOUTDRV;

	writeRegister(PCA9685_MODE_2_REG, mode_2);
}

void PCA9685::writeRegister (uint8_t reg, uint8_t value)
{
	Wire.beginTransmission(_i2c_address);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}
