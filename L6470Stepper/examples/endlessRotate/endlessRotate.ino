#include <SPI.h> 			// also need to include SPI
#include <L6470Stepper.h>	// include library

#define pinCS	10
L6470Stepper stepper(pinCS);	// pass CS pin number

void setup()
{
	stepper.setup();
	stepper.rotate(CW);		// pass CW or CCW
}

void loop()
{
}

