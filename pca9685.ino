#include <PCA9685.h>

PCA9685 pwm = PCA9685();

void setup ()
{
	Serial.begin(9600);
	Serial.println("PCA9685 16 channel PWM test!");

	pwm.begin();
}

void loop ()
{
}
