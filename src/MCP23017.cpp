#include "MCP23017.h"

// MCP23017 Register Address
#define MCP23017_GPIO 0x09  // Port register
#define MCP23017_GPPU 0x06  // Pull-up resistor configuration register
#define MCP23017_IOCON 0x05 // Configuration register
#define MCP23017_IODIR 0x00 // I/O direction register
#define MCP23017_IPOL 0x01  // Input polarity register

// #define MCP23017_DEFVAL 0x03		// Default compare register for interrupt-on-change
// #define MCP23017_GPINTEN 0x02	// Interrupt-on-change control register
// #define MCP23017_INTCAP 0x08		// Interrupt capture register
// #define MCP23017_INTCON 0x04		// Interrupt control register
// #define MCP23017_INTF 0x07  		// Interrupt flag register
// #define MCP23017_OLAT 0x0A  		// Output latch register

bool MCP23017::begin ()
{
	Wire.begin();

	// Set all pins to outputs
	writeRegister(MCP23017_IODIR, 0x00);

	// Set all pins to active high (not inverted)
	writeRegister(MCP23017_IPOL, 0x00);

	// Enable pull-up resistors on all pins
	writeRegister(MCP23017_GPPU, 0xFF);

	return true;
}

bool MCP23017::digitalRead (uint8_t pin)
{
	// Read the GPIO register which contains the current state of all pins.
	uint8_t gpio_state = readRegister(MCP23017_GPIO);

	// Use a bit mask to isolate the state of the specified pin.
	// Shift right by 'pin' and mask with 0x01 to get the state of the specific pin.
	return (gpio_state >> pin) & 0x01;
}

uint8_t MCP23017::digitalReadAll ()
{
	uint8_t gpio_state = readRegister(MCP23017_GPIO);

	return gpio_state;
}
