#include <SPI.h> 			// also need to include SPI
#include <L6470Stepper.h>	// include library

#define CHAINED_MOTOR_NUM	2
#define pinCS	10
L6470Stepper stepper(pinCS, CHAINED_MOTOR_NUM);	// pass CS pin number & number of chained motors 

void setup()
{
	// stepper.setup();												// if nothing passes, default parameter for small motor is assigned
	// stepper.setup(registerForSmallMotor);						// you can set your own parameters for L6470
	// stepper.setup(registerForL6470, REGISTER_SIZE_6480);			// if you use L6480, you can manipulate them in the same way
	stepper.setup(registerForSmallMotor, REGISTER_SIZE_SML, 0);		// of course, differnt parameter can be assigned to each motors
	stepper.setup(registerForMidiumMotor, REGISTER_SIZE_MID, 1);	// motor id 0: farthest from arduino, and id n: nearset
	
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

