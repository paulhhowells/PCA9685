#include "PCA9685.h"

// PCA9685 Register Addresses
#define PCA9685_MODE_1_REG 0x00       // Mode 1 register address
#define PCA9685_MODE_2_REG 0x01       // Mode 2 register address
#define PCA9685_MODE_2_REGOUTDRV 0x04 // Bit 2 controls output mode
#define PCA9685_PRESCALE 0xFE         // Prescaler for PWM output frequency

#define frequencyHz 1600

// Public methods:

bool PCA9685::begin ()
{
	Wire.begin();

	setOpenDrainOutputMode();
	setFrequency(frequencyHz);

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

void PCA9685::setFrequency (uint16_t frequency)
{
	uint8_t prescale = round(((float)25000000 / (float)(frequency * (long)4096))) - 1;
	setPreScale(prescale);
}

void PCA9685::setPWMDuty (uint8_t pin, uint16_t on, uint16_t off)
{
	uint8_t control_register = PCA9685_LED_0_ON_L + (4 * pin); // Address for Control Register
	// on will be 0 - 4095 = 12bit
	// buffer 1 gets lowest byte of 16bit
	// buffer 2 gets highest byte shifted into a byte as 0000xxxx

	uint8_t buffer[5];
	buffer[0] = control_register;

	// Data Registers
	buffer[1] = on;       // LED_pin_ON_H
	buffer[2] = on >> 8;  // LED_pin_ON_L
	buffer[3] = off;      // LED_pin_OFF_H
	buffer[4] = off >> 8; // LED_pin_OFF_L

	Wire.beginTransmission(_i2c_address);
	Wire.write(buffer, 5);
	Wire.endTransmission();
}

// Private methods:

void PCA9685::setPreScale (uint8_t prescale)
{
	// Must be in sleep mode to set the prescaler.
	sleep();
	writeRegister(PCA9685_PRESCALE, prescale);
	wake();
}

void PCA9685::sleep ()
{
	uint8_t mode_1 = readRegister(PCA9685_MODE_1_REG); // Get current mode_1
	bitSet(mode_1, 4);                                 // Set sleep mode by setting bit 4 to 1
	writeRegister(PCA9685_MODE_1_REG, mode_1);         // Go to sleep.
	delay(1);                                          // Delay by at least 500 µs
}

void PCA9685::wake ()
{
	uint8_t mode_1 = readRegister(PCA9685_MODE_1_REG); // Get current mode_1
	bitClear(mode_1, 4);                               // Set normal awake mode by setting bit 4 to 0.
	writeRegister(PCA9685_MODE_1_REG, mode_1);         // Wake up.
	delay(1);                                          // Delay by at least 500 µs
}
