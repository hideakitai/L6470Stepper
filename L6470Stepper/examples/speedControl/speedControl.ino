#include <SPI.h> 			// also need to include SPI
#include <L6470Stepper.h>	// include library

#define pinCS	10
L6470Stepper stepper(pinCS);	// pass CS pin number

void setup()
{
	stepper.setup();
	stepper.setRps(200);	// default is 200 rps at 200 step motor
	stepper.angle(0);
}

void loop()
{
	static boolean goForward = true;

	delay(5000);

	if (goForward) {
		stepper.setRps(100);
		stepper.angle(360);
	} else {
		stepper.setRps(200);
		stepper.angle(0);
	}

	// switch direction
	goForward = !goForward;
}

