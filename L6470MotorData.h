#ifndef L6470MOTORDATA_H_INCLUDED
#define L6470MOTORDATA_H_INCLUDED

#include "L6470Common.h"

static const float SPD_RES_LIMIT		= 15.25;	// L6470 defined available MAX/MIN_SPEED resolution
static const float ACC_RES_LIMIT		= 14.55;	// L6470 defined available MAX/MIN_ACC resolution
static const float SPD_RES_COMMAND		= 0.015;	// L6470 defined available constant speed command resolution

static const uint8_t BITMASK_DIR		= 0x01;
static const uint8_t BITMASK_ACT		= 0x08;
static const uint8_t BITMASK_REG		= 0x1F;
static const uint32_t BITMASK_SIGN		= 0x200000;

static const int DEFAULT_MOTOR_STEP		= 200;
static const int WRITABLE_REG_NUM_L6470	= 19;
static const int WRITABLE_REG_NUM_L6480	= 21;

enum initDriverType {
	L6470_REGISTER,
	L6480_REGISTER
};

// Application Command Tables for L6470 / L6480 -----------------------------------------

typedef struct {
	uint8_t cmd;
	uint8_t size;
	uint32_t mask;
} _L6470AppCmdTable;

const static _L6470AppCmdTable L6470AppCmdTable[] =
{
	// cmd, size of data (bytes), bitmask
	{0x00, 0x00, 0x000000},	// NOP
	{0x00, 0x03, 0xFFFFFF},	// SETPARAM	// bitmask is set by register manipulation
	{0x20, 0x00, 0x000000},	// GETPARAM
	{0x50, 0x03, 0x0FFFFF},	// RUN
	{0x58, 0x00, 0x000000},	// STEPCLOCK
	{0x40, 0x03, 0x3FFFFF},	// MOVE
	{0x60, 0x03, 0x3FFFFF},	// GOTO
	{0x68, 0x03, 0x3FFFFF},	// GOTO_DIR
	{0x82, 0x03, 0x0FFFFF},	// GOUNTIL
	{0x92, 0x00, 0x000000},	// RELEASESW
	{0x70, 0x00, 0x000000},	// GOHOME
	{0x78, 0x00, 0x000000},	// GOMARK
	{0xD8, 0x00, 0x000000},	// RESETPOS
	{0xC0, 0x00, 0x000000},	// RESETDEVICE
	{0xB0, 0x00, 0x000000},	// SOFTSTOP
	{0xB8, 0x00, 0x000000},	// HARDSTOP
	{0xA0, 0x00, 0x000000},	// SOFTHIZ
	{0xA8, 0x00, 0x000000},	// HARDHIZ
	{0xD0, 0x00, 0x000000}	// GETSTATUS
};


// Register Tables for L6470 / L6480 -----------------------------------------

// switch if driver is L6470 or L6480
typedef struct  {
	uint8_t reg;
	uint8_t size;
	uint32_t mask;
} _L6470RegTable;

static const _L6470RegTable L6470RegTable[] =
{
	// cmd, size of data (bytes), bitmask
	{0x00, 0x00, 0x000000},	// NOP,
	{0x01, 0x03, 0x3FFFFF},	// RW REG_ABS_POS,
	{0x02, 0x02, 0x0001FF},	// RW REG_EL_POS,
	{0x03, 0x03, 0x3FFFFF},	// RW REG_MARK,
	{0x04, 0x03, 0x0FFFFF},	// R  REG_SPEED,
	{0x05, 0x02, 0x000FFF},	// RW REG_ACC,
	{0x06, 0x02, 0x000FFF},	// RW REG_DEC,
	{0x07, 0x02, 0x0003FF},	// RW REG_MAX_SPEED,
	{0x08, 0x02, 0x001FFF},	// RW REG_MIN_SPEED,
	{0x09, 0x01, 0x0000FF},	// RW REG_KVAL_HOLD,
	{0x0A, 0x01, 0x0000FF},	// RW REG_KVAL_RUN,
	{0x0B, 0x01, 0x0000FF},	// RW REG_KVAL_ACC,
	{0x0C, 0x01, 0x0000FF},	// RW REG_KVAL_DEC,
	{0x0D, 0x02, 0x003FFF},	// RW REG_INT_SPEED,
	{0x0E, 0x01, 0x0000FF},	// RW REG_ST_SLP,
	{0x0F, 0x01, 0x0000FF},	// RW REG_FN_SLP_ACC,
	{0x10, 0x01, 0x0000FF},	// RW REG_FN_SLP_DEC,
	{0x11, 0x01, 0x00000F},	// RW REG_K_THERM,
	{0x12, 0x01, 0x00001F},	// R  REG_ADC_OUT,
	{0x13, 0x01, 0x00000F},	// RW REG_OCD_THRESH,
	{0x14, 0x01, 0x00007F},	// RW REG_STALL_THRESH,
	{0x15, 0x02, 0x0003FF},	// RW REG_FS_SPD,
	{0x16, 0x01, 0x0000FF},	// RW REG_STEP_MODE,
	{0x17, 0x01, 0x0000FF},	// RW REG_ALARM_EN,
	{0x18, 0x02, 0x00FFFF},	// RW REG_CONFIG,
	{0x19, 0x02, 0x00FFFF}	// R  REG_STATUS
};

static const _L6470RegTable L6480RegTable[] =
{
	// cmd, size of data (bytes), bitmask
	{0x00, 0x00, 0x000000},	//    REG_NOP
	{0x01, 0x03, 0x3FFFFF},	// RW REG_ABS_POS
	{0x02, 0x02, 0x0001FF},	// RW REG_EL_POS
	{0x03, 0x03, 0x3FFFFF},	// RW REG_MARK
	{0x04, 0x03, 0x0FFFFF},	// R  REG_SPEED
	{0x05, 0x02, 0x000FFF},	// RW REG_ACC
	{0x06, 0x02, 0x000FFF},	// RW REG_DEC
	{0x07, 0x02, 0x0003FF},	// RW REG_MAX_SPEED
	{0x08, 0x02, 0x001FFF},	// RW REG_MIN_SPEED
	{0x09, 0x01, 0x0000FF},	// RW REG_KVAL_HOLD
	{0x0A, 0x01, 0x0000FF},	// RW REG_KVAL_RUN
	{0x0B, 0x01, 0x0000FF},	// RW REG_KVAL_ACC
	{0x0C, 0x01, 0x0000FF},	// RW REG_KVAL_DEC
	{0x0D, 0x02, 0x003FFF},	// RW REG_INT_SPEED
	{0x0E, 0x01, 0x0000FF},	// RW REG_ST_SLP
	{0x0F, 0x01, 0x0000FF},	// RW REG_FN_SLP_ACC
	{0x10, 0x01, 0x0000FF},	// RW REG_FN_SLP_DEC
	{0x11, 0x01, 0x00000F},	// RW REG_K_THERM
	{0x12, 0x01, 0x00001F},	// R  REG_ADC_OUT
	{0x13, 0x01, 0x00000F},	// RW REG_OCD_THRESH
	{0x14, 0x01, 0x00007F},	// RW REG_STALL_THRESH
	{0x15, 0x02, 0x0003FF},	// RW REG_FS_SPD
	{0x16, 0x01, 0x0000FF},	// RW REG_STEP_MODE
	{0x17, 0x01, 0x0000FF},	// RW REG_ALARM_EN
	{0x1A, 0x02, 0x00FFFF},	// RW REG_CONFIG	// address changed in L6480
	{0x1B, 0x02, 0x00FFFF},	// R  REG_STATUS	// address changed in L6480
	{0x18, 0x02, 0x0007FF},	// RW REG_GATECFG1
	{0x19, 0x01, 0x0000FF}	// RW REG_GATECFG2
};


typedef struct {
	uint8_t cmd;
	uint8_t size;
	uint32_t value;
} _L6470CmdStruct;

class L6470MotorData
{
public:
	L6470MotorData();
	~L6470MotorData();

	void	setup(initDriverType type);
	void	setMotorStep(int motorStep);

	void	setAction(int appCmd, int val = 0, int dir = 0, int act = 0);
	void	setRegister(int reg, int val = 0);
	void	requestRegister(int reg);

	// for SPI data generation
	uint8_t getAppCmd();
	uint8_t getAppSize();
	uint32_t getAppValue();

	uint8_t getRegCmd();
	uint8_t getRegSize();
	uint32_t getRegValue();

	bool	isCmdChanged();
	bool	isRegChanged();
	bool	isRegRequested();

	void	setCmdChanged(bool needToSetCmd);
	void	setRegChanged(bool needToSetReg);
	void	setRegRequested(bool needToGetReg);

	int		getCurRps();

	int 	getMotorStep(){return _motorStep;};
	int 	getMicroStep(){return _microStep;};

	void	clearCmd(){_appCmd.cmd = 0; _appCmd.size = 0; _appCmd.value = 0;};
	void	clearReg(){_regCmd.cmd = 0; _regCmd.size = 0; _regCmd.value = 0;};

protected:
	_L6470RegTable	*_regTable;
private:

	void	setAppCmd(int cmd);
	void	setAppSize(int size);
	void	setAppValue(int val, int appCmd);

	void	setRegCmd(int cmd);
	void	setRegSize(int size);
	void	setRegValue(int val, int regCmd);

	bool	_needToSetCmd;
	bool	_needToSetReg;
	bool	_needToGetReg;

	_L6470CmdStruct 	_appCmd;
	_L6470CmdStruct 	_regCmd;

	int		_curRps;
	int		_motorStep;
	L6470MicroStepList	_microStep;
};



#endif
