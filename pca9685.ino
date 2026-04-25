#include <PCA9685.h>

/**
 * PCA9685 16 channel PWM test
 * Use this to set the PCA9685 to open-drain output mode and test each pin by turning it fully on for 1 second, then fully off for 1 second.
 * Initially intended for testing the Adafruit PCA9685 board(https://www.adafruit.com/product/815).
 * Attach LED anodes to external 5v+ supply which is made available on pin row 2.
 * Attach LED cathodes to pin row 1 which connects via a current limiting 220 ohm resistor to PWM.
 * Ignore pin row 3 which connects to ground.
 */

PCA9685 pca9685 = PCA9685();

void setup ()
{
	Serial.begin(9600);
	Serial.println("PCA9685 16 channel PWM test!");

	pca9685.begin();
}

void loop ()
{
	static uint16_t oneSecond = 1000;

	for (uint8_t pin = 0; pin < 16; pin++)
	{
		pca9685.setPWMDuty(pin, 4096, 0); // turn pin fully on
		delay(oneSecond);
		pca9685.setPWMDuty(pin, 0, 4096); // turn pin fully off
	}

	delay(oneSecond);
}
