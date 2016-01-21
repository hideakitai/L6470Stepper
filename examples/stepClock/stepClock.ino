#include <SPI.h> 			// also need to include SPI
#include <L6470Stepper.h>	// include library

#define USE_DRIVER_L6480

#define pinCS	10
int steps[4] = {1440};    // left angle, left speed, right angle, right speed
#define	REGISTER_SIZE_L6470	19
#define	REGISTER_SIZE_L6480	21

#ifndef USE_DRIVER_L6480
#define REGISTER_SIZE REGISTER_SIZE_L6470
L6470Stepper stepper(pinCS, 1, steps);	// pass CS pin number & number of chained motors
registerStruct params[REGISTER_SIZE_L6470] =
{
	// register			// value
	{ REG_ACC,			0x040	},
	{ REG_DEC,			0x040	},
	{ REG_MAX_SPEED,	800		},	// rps - available by 488 rps in small motor
	{ REG_MIN_SPEED,	0		},	// rps
	{ REG_KVAL_HOLD,	0x50	},
	{ REG_KVAL_RUN,		0x40	},
	{ REG_KVAL_ACC,		0x40	},
	{ REG_KVAL_DEC,		0x40	},
	{ REG_INT_SPEED,	0x3FFF	},
	{ REG_ST_SLP,		0x37	},
	{ REG_FN_SLP_ACC,	0x3E	},
	{ REG_FN_SLP_DEC,	0x3E	},
	{ REG_K_THERM,		0x00	},
	{ REG_OCD_THRESH,	0x08	},
	{ REG_STALL_THRESH,	0x7F	},
	{ REG_FS_SPD,		0x27	},
	{ REG_STEP_MODE,	0x07	},	// MICROSTEP_DIV128
	{ REG_ALARM_EN,		0xFF	},
	{ REG_CONFIG,		0x2E88	}
};
#else
#define REGISTER_SIZE REGISTER_SIZE_L6480
L6480Stepper stepper(pinCS, 1, steps);	// pass CS pin number & number of chained motors
registerStruct params[REGISTER_SIZE_L6480] =
{
    { REG_ACC,			0x040	},
	{ REG_DEC,			0x040	},
	{ REG_MAX_SPEED,	800		},	// rps - available by 488 rps in small motor
	{ REG_MIN_SPEED,	0		},	// rps
	{ REG_KVAL_HOLD,	0x40	},
	{ REG_KVAL_RUN,		0x40	},
	{ REG_KVAL_ACC,		0x40	},
	{ REG_KVAL_DEC,		0x40	},
	{ REG_INT_SPEED,	0x3FFF	},
	{ REG_ST_SLP,		0x37	},
	{ REG_FN_SLP_ACC,	0x3E	},
	{ REG_FN_SLP_DEC,	0x3E	},
	{ REG_K_THERM,		0x00	},
	{ REG_OCD_THRESH,	0x08	},
	{ REG_STALL_THRESH,	0x7F	},
	{ REG_FS_SPD,		0x27	},
	{ REG_STEP_MODE,	0x00	},	// MICROSTEP_DIV128
	{ REG_ALARM_EN,		0xFF	},
	{ REG_GATECFG1,		0x00	},	// new in L6480
	{ REG_GATECFG2,		0x00	},	// new in L6480
	{ REG_CONFIG,		0x3708	}	// changed from L6470
};
#endif

long curr_step = 0;
float curr_angle = 0.;

void setup()
{
    Serial.begin(57600);
	stepper.setup(params, REGISTER_SIZE);		// of course, differnt parameter can be assigned to each motors

	// motion test
    stepper.angle(90);
    delay(3000);

	// motion test
    stepper.angle(0);
	delay(3000);

	stepper.setStepEnable(3);
}

void loop()
{
	static bool cw = true;

	if (cw)
	{
		stepper.stepClock(90., 2000.);
	}
	else
	{
		stepper.stepClock(-90., 2000.);
	}

	delay(5000);
	cw = !cw;

	Serial.println(stepper.getCurrAngle());
}
