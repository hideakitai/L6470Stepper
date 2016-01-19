#include <SPI.h> 			// also need to include SPI
#include <L6470Stepper.h>	// include library

#define CHAINED_MOTOR_NUM	2
#define pinCS	10

L6470Stepper stepper(pinCS, CHAINED_MOTOR_NUM);	// pass CS pin number & number of chained motors

void setup()
{
	stepper.setup();
	stepper.angle(0);	// this makes all motors do the same motion
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

