#include <SPI.h> 			// also need to include SPI
#include <L6470Stepper.h>	// include library

#define pinCS	10
L6480Stepper stepper(pinCS);	// change L6470Stepper -> L6480Stepper, other use is the same as L6470Stepper

void setup()
{
	stepper.setup();
	stepper.angle(0);
}

void loop()
{
	static boolean goForward = true;
	delay(2000);

	if (goForward) {
		stepper.angle(360);
	} else {
		stepper.angle(0);
	}

	// switch direction
	goForward = !goForward;
}

