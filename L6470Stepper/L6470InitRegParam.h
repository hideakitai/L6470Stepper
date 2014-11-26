#ifndef L6470INITREGPARAM_H_INCLUDED
#define L6470INITREGPARAM_H_INCLUDED

// default parameters for small motor -----------------------------------------
// 
// if you dont pass any register parameter list, 
// this array is assigned for initialization of L6470

typedef struct {
	int	reg;
	int	val;
} registerStruct;

volatile static registerStruct L6470DefaultRegParamList[] = {
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

volatile static registerStruct L6480DefaultRegParamList[] = {
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

#endif
