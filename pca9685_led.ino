#include <Wire.h>

// PCA9685 Register Addresses
#define PCA9685_I2C_ADDRESS 0x40 // Default 7 bit I2C address

#define PCA9685_MODE_1_REG 0x00       // Mode 1 register address
#define PCA9685_MODE_2_REG 0x01       // Mode 2 register address
#define PCA9685_MODE_2_REGOUTDRV 0x04 // Bit 2 controls output mode
#define PCA9685_PRESCALE 0xFE         // Prescaler for PWM output frequency

#define PCA9685_LED_0_ON_L 0x06  // LED0 on mark, low byte 8 LSBs
#define PCA9685_LED_0_ON_H 0x07  // LED0 on mark, high byte 4 MSBs
#define PCA9685_LED_0_OFF_L 0x08 // LED0 off mark, low byte
#define PCA9685_LED_0_OFF_H 0x09 // LED0 off mark, high byte
	                             // etc all 16:  LED15_OFF_H 0x45

void setup ()
{
	Serial.begin(9600);
	Serial.println("16 channel PWM test!");

	initPCA9685(); // Initialise the PCA9685
}

void loop ()
{
	for (uint8_t pin = 0; pin < 16; pin++)
	{
		setPWMDuty(pin, 4096, 0); // turns pin fully on
		delay(100);
		setPWMDuty(pin, 0, 4096); // turns pin fully off
	}
}

// START code for controlling the PCA9685
// TODO: convert to a library.

// Initialise the PCA9685
void initPCA9685 ()
{
	setOpenDrainOutputMode();
	setFrequency(1600); // 1600 Hz
}

void setPWMDuty (uint8_t pin, uint16_t on, uint16_t off)
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

	Wire.begin();
	Wire.beginTransmission(PCA9685_I2C_ADDRESS);
	Wire.write(buffer, 5);
	Wire.endTransmission();
}

void setOpenDrainOutputMode ()
{
	// Set Mode 2 to open drain instead of totum pole output.

	// Configure open-drain mode
	uint8_t mode_2 = readRegister(PCA9685_MODE_2_REG);

	// Use a mask to set the OUTDRV bit to 0 for open-drain
	mode_2 &= ~PCA9685_MODE_2_REGOUTDRV;

	writeRegister(PCA9685_MODE_2_REG, mode_2);
	// uint8_t buffer[2] = {PCA9685_MODE2, newmode}; // 0x01 & 1011
	// Wire.write(buffer, 2);

	Serial.println("PCA9685 configured for open-drain mode");
}

// Set PWM Frequency 40 - 1000Hz
void setFrequency (uint16_t frequency)
{
	uint8_t prescale = round(((float)25000000 / (float)(frequency * (long)4096))) - 1;
	setPreScale(prescale);
}

void setPreScale (uint8_t prescale)
{
	// Must be in sleep mode to set the prescaler.
	sleep();
	writeRegister(PCA9685_PRESCALE, prescale);
	wake();
}

void sleep ()
{
	uint8_t mode_1 = readRegister(PCA9685_MODE_1_REG); // Get current mode_1
	bitSet(mode_1, 4);                                 // Set sleep mode by setting bit 4 to 1
	writeRegister(PCA9685_MODE_1_REG, mode_1);         // Go to sleep.
	delay(1);                                          // Delay by at least 500 µs
}

void wake ()
{
	uint8_t mode_1 = readRegister(PCA9685_MODE_1_REG); // Get current mode_1
	bitClear(mode_1, 4);                               // Set normal awake mode by setting bit 4 to 0.
	writeRegister(PCA9685_MODE_1_REG, mode_1);         // Wake up.
	delay(1);                                          // Delay by at least 500 µs
}

uint8_t readRegister (uint8_t reg)
{
	Wire.beginTransmission(PCA9685_I2C_ADDRESS);
	Wire.write(reg);
	Wire.endTransmission();

	// Wire.requestFrom(PCA9685_I2C_ADDRESS, (uint8_t)1);
	uint8_t request_quantity = 1;
	Wire.requestFrom(PCA9685_I2C_ADDRESS, request_quantity);

	return Wire.read();
}

void writeRegister (uint8_t reg, uint8_t value)
{
	Wire.beginTransmission(PCA9685_I2C_ADDRESS);
	Wire.write(reg);
	Wire.write(value);
	Wire.endTransmission();
}

// END code for controlling the PCA9685
