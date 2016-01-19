#include <L6470Stepper.h>	// include library

// you can set only a few registers, of cource
#define	REGISTER_SIZE_SML	19
#define	REGISTER_SIZE_MID	19
#define REGISTER_SIZE_6480	21

// this array is for the initialization of L6470 registers
// the size of the array must be 19
registerStruct registerForSmallMotor[REGISTER_SIZE_SML] = 
{
	// register			// value
	{ REG_ACC,			0x040	},
	{ REG_DEC,			0x040	},
	{ REG_MAX_SPEED,	200		},	// rps - available by 488 rps in small motor
	{ REG_MIN_SPEED,	0		},	// rps
	{ REG_KVAL_HOLD,	0xFF	},
	{ REG_KVAL_RUN,		0xFF	},
	{ REG_KVAL_ACC,		0xFF	},
	{ REG_KVAL_DEC,		0xFF	},
	{ REG_INT_SPEED,	0x408	},
	{ REG_ST_SLP,		0x19	},
	{ REG_FN_SLP_ACC,	0x29	},
	{ REG_FN_SLP_DEC,	0x29	},
	{ REG_K_THERM,		0x00	},
	{ REG_OCD_THRESH,	0x08	},
	{ REG_STALL_THRESH,	0x7F	},
	{ REG_FS_SPD,		0x27	},
	{ REG_STEP_MODE,	0x07	},	// MICROSTEP_DIV128
	{ REG_ALARM_EN,		0xFF	},
	{ REG_CONFIG,		0x2E88	}
};

registerStruct registerForMidiumMotor[REGISTER_SIZE_MID] = 
{
	// register			// value
	{ REG_ACC,			0x220	},
	{ REG_DEC,			0x200	},
	{ REG_MAX_SPEED,	2000	},	// rps - available by 488 rps in small motor
	{ REG_MIN_SPEED,	0		},	// rps
	{ REG_KVAL_HOLD,	0x3F	},
	{ REG_KVAL_RUN,		0x3F	},
	{ REG_KVAL_ACC,		0x64	},
	{ REG_KVAL_DEC,		0x32	},
	{ REG_INT_SPEED,	0x3E8	},
	{ REG_ST_SLP,		0x50	},
	{ REG_FN_SLP_ACC,	0x28	},
	{ REG_FN_SLP_DEC,	0x00	},
	{ REG_K_THERM,		0x00	},
	{ REG_OCD_THRESH,	0x08	},
	{ REG_STALL_THRESH,	0x7F	},
	{ REG_FS_SPD,		0x126	},
	{ REG_STEP_MODE,	0x07	},	// MICROSTEP_DIV128
	{ REG_ALARM_EN,		0xFF	},
	{ REG_CONFIG,		0x2E88	}
};

registerStruct registerForL6480[REGISTER_SIZE_6480] = {
	{ REG_ACC,			0x08A	},
	{ REG_DEC,			0x08A	},
	{ REG_MAX_SPEED,	200		},	// rps - available by 488 rps in small motor
	{ REG_MIN_SPEED,	0		},	// rps
	{ REG_KVAL_HOLD,	0xFF	},
	{ REG_KVAL_RUN,		0xFF	},
	{ REG_KVAL_ACC,		0xFF	},
	{ REG_KVAL_DEC,		0xFF	},
	{ REG_INT_SPEED,	0x508	},
	{ REG_ST_SLP,		0x19	},
	{ REG_FN_SLP_ACC,	0x29	},
	{ REG_FN_SLP_DEC,	0x29	},
	{ REG_K_THERM,		0x00	},
	{ REG_OCD_THRESH,	0x08	},
	{ REG_STALL_THRESH,	0x7F	},
	{ REG_FS_SPD,		0x27	},
	{ REG_STEP_MODE,	0x07	},	// MICROSTEP_DIV128
	{ REG_ALARM_EN,		0xFF	},
	{ REG_GATECFG1,		0x00	},	// new in L6480
	{ REG_GATECFG2,		0x00	},	// new in L6480
	{ REG_CONFIG,		0x3708	}	// changed from L6470
};

