#ifndef _DEBUG_SPI_H
#define _DEBUG_SPI_H

#include <spi4teensy3.h>
#include <SPI.h>
#include "DebugSerial.h"

/*
 * Debug print SPI pins
 */
void debug_print_SPI_pins()
{
	// Teensy 3.2:
	// PIN_SPI_SCK=13
	// PIN_SPI_MOSI=11
	// PIN_SPI_MISO=12
	// PIN_SPI_SS=10

	DEBUG_PRINT("PIN_SPI_SCK=");
	DEBUG_PRINTLN(PIN_SPI_SCK);
	DEBUG_PRINT("PIN_SPI_MOSI=");
	DEBUG_PRINTLN(PIN_SPI_MOSI);
	DEBUG_PRINT("PIN_SPI_MISO=");
	DEBUG_PRINTLN(PIN_SPI_MISO);
	DEBUG_PRINT("PIN_SPI_SS=");
	DEBUG_PRINTLN(PIN_SPI_SS);
}

/*
 * Debug print SPI parameters
 */
void debug_print_SPI_parameters()
{
	#if defined(USING_SPI4TEENSY3)
		DEBUG_PRINTLN("DEFINED: USING_SPI4TEENSY3");
	#else
		DEBUG_PRINTLN("UNDEFINED: USING_SPI4TEENSY3");
	#endif

	#if defined(CORE_TEENSY)
		DEBUG_PRINTLN("DEFINED: CORE_TEENSY");
	#else
		DEBUG_PRINTLN("UNDEFINED: CORE_TEENSY");
	#endif

	#if defined(KINETISK)
		DEBUG_PRINTLN("DEFINED: KINETISK");
	#else
		DEBUG_PRINTLN("UNDEFINED: KINETISK");
	#endif

	debug_print_SPI_pins();
}

/*
 * Debug loop forever with SPI SS pin
 */
void debug_loop_forever_test_SPI_SS_PIN()
{
	// SS pin
	const int slaveSelectPin = 10;
	// set the slaveSelectPin as an output:
	pinMode (slaveSelectPin, OUTPUT);

	DEBUG_PRINTLN("debug_loop_forever_test_SPI_SS_PIN()");

	while (1)
	{
		digitalWrite(slaveSelectPin, LOW);
		delayMicroseconds(1);
		digitalWrite(slaveSelectPin, HIGH);
		delayMicroseconds(1);
	}
}

/*
 * Debug set teensy3 parameters
 */
void debug_set_spi4teensy3_parameters()
{
	spi4teensy3::init(7);
	SPI.setClockDivider(SPI_CLOCK_DIV128);
}

#endif
