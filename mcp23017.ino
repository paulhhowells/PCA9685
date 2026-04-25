#include <MCP23017.h>

#define BUTTON_PIN 1 // MCP23017 pin button is attached to

MCP23017 mcp23017 = MCP23017();

void setup ()
{
	Serial.begin(9600);
	Serial.println("MCP23017 test");

	mcp23017.begin();
}

void loop ()
{
	static bool switch_1 = false;

	// LOW = pressed, HIGH = not pressed
	if (!mcp23017.digitalRead(uint8_t BUTTON_PIN))
	{
		Serial.println("Button Pressed!");

		// debounce?
		// if button_1 is changed ( !== static ) then
		// set led accordingly

		delay(100);
	}
}
