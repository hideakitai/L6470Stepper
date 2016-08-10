#ifndef L6470COMMON_H_INCLUDED
#define L6470COMMON_H_INCLUDED

#include <Arduino.h>
#include "pins_arduino.h"

// Application Command Lists -----------------------------------------

enum AppCmdList
{
	NOP	= 0x00,
	SETPARAM,	// 0-4 bit is ORed by register
	GETPARAM,	// 0-4 bit is ORed by register
	RUN,
	STEPCLOCK,
	MOVE,
	GOTO,
	GOTO_DIR,
	GOUNTIL,
	RELEASESW,
	GOHOME,
	GOMARK,
	RESETPOS,
	RESETDEVICE,
	SOFTSTOP,
	HARDSTOP,
	SOFTHIZ,
	HARDHIZ,
	GETSTATUS
};


// Register Lists -----------------------------------------

enum RegList
{
	REG_NOP = 0x00,
	REG_ABS_POS,
	REG_EL_POS,
	REG_MARK,
	REG_SPEED,
	REG_ACC,
	REG_DEC,
	REG_MAX_SPEED,
	REG_MIN_SPEED,
	REG_KVAL_HOLD,
	REG_KVAL_RUN,
	REG_KVAL_ACC,
	REG_KVAL_DEC,
	REG_INT_SPEED,
	REG_ST_SLP,
	REG_FN_SLP_ACC,
	REG_FN_SLP_DEC,
	REG_K_THERM,
	REG_ADC_OUT,
	REG_OCD_THRESH,
	REG_STALL_THRESH,
	REG_FS_SPD,
	REG_STEP_MODE,
	REG_ALARM_EN,
	REG_CONFIG,		// address changed from L6470
	REG_STATUS,		// address changed from L6470
	REG_GATECFG1,	// new in L6480
	REG_GATECFG2	// new in L6480
};


// Other Definitions -----------------------------------------
typedef enum _L6470MicroStepList
{
	MICROSTEP_FULL = 0x00,
	MICROSTEP_HALF,
	MICROSTEP_DIV4,
	MICROSTEP_DIV8,
	MICROSTEP_DIV16,
	MICROSTEP_DIV32,
	MICROSTEP_DIV64,
	MICROSTEP_DIV128
} L6470MicroStepList;

typedef enum _motorDirection {
	CCW,
	CW
} motorDirection;


#endif	// L6470COMMON_H_INCLUDED
