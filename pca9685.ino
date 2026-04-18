#include <PCA9685.h>

PCA9685 pca9685 = PCA9685();

void setup ()
{
	Serial.begin(9600);
	Serial.println("PCA9685 16 channel PWM test!");

	pca9685.begin();
}

void loop ()
{
	for (uint8_t pin = 0; pin < 16; pin++)
	{
		pca9685.setPWMDuty(pin, 4096, 0); // turns pin fully on
		delay(1000);
		pca9685.setPWMDuty(pin, 0, 4096); // turns pin fully off
	}
}
