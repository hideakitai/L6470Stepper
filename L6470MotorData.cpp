#include "L6470MotorData.h"


L6470MotorData::L6470MotorData()
{
	_motorStep = DEFAULT_MOTOR_STEP;
	_microStep = MICROSTEP_DIV128;
	_needToSetCmd = false;
	_needToSetReg = false;
	_regTable = NULL;
}

L6470MotorData::~L6470MotorData()
{

}

void L6470MotorData::setup(initDriverType type)
{
	if (type == L6470_REGISTER) {
		_regTable = (_L6470RegTable*)L6470RegTable;
	} else if (type == L6480_REGISTER) {
		_regTable = (_L6470RegTable*)L6480RegTable;
	}
}

void L6470MotorData::setMotorStep(int motorStep)
{
	_motorStep = motorStep;
}

void L6470MotorData::setAction(int appCmd, int val, int dir, int act)
{
	// the behavior of motors by applicaiton command depends on all register settings of L6470
	// so just setting cmd & data size here
	// after that, value of command is updated in loop() by update()

	int cmd = L6470AppCmdTable[appCmd].cmd;	// original app command
	cmd |= ((dir << 0) & BITMASK_DIR);
	cmd |= ((act << 3) & BITMASK_ACT);

	setAppCmd(cmd);
	setAppSize(L6470AppCmdTable[appCmd].size);
	setAppValue((val & (L6470AppCmdTable[appCmd].mask)), appCmd);

	setCmdChanged(true);
}

void L6470MotorData::setRegister(int reg, int val)
{
	int cmd = L6470AppCmdTable[SETPARAM].cmd;				// SETPARAM cmd = SETPARAM + register
	cmd |= ((_regTable[reg].reg << 0) & BITMASK_REG);	// REG bits are bit 0-4 (PARAM bits)

	setRegCmd(cmd);
	setRegSize(_regTable[reg].size);
	setRegValue((val & _regTable[reg].mask), _regTable[reg].reg);

	if(_regTable[reg].reg == REG_STEP_MODE) {
		_microStep = (L6470MicroStepList)val;
	}

	setRegChanged(true);
}

void L6470MotorData::requestRegister(int reg)
{
	int cmd = L6470AppCmdTable[GETPARAM].cmd;	// GETPARAM cmd = GETPARAM + register
	cmd |= ((_regTable[reg].reg << 0) & BITMASK_REG);			// REG bits are bit 0-4 (PARAM bits)

	setRegCmd(cmd);
	setRegSize(_regTable[reg].size);
	setRegValue((0 & _regTable[reg].mask), _regTable[reg].reg);	// send NOP data

	setRegRequested(true);
}

bool L6470MotorData::isCmdChanged()
{
	return _needToSetCmd;
}

bool L6470MotorData::isRegChanged()
{
	return _needToSetReg;
}

bool L6470MotorData::isRegRequested()
{
	return _needToGetReg;
}

void L6470MotorData::setCmdChanged(bool needToSetCmd)
{
	_needToSetCmd = needToSetCmd;
}

void L6470MotorData::setRegChanged(bool needToSetReg)
{
	_needToSetReg = needToSetReg;
}

void L6470MotorData::setRegRequested(bool needToGetReg)
{
	_needToGetReg = needToGetReg;
}


void L6470MotorData::setAppCmd(int cmd)
{
	_appCmd.cmd = cmd;
}

void L6470MotorData::setAppSize(int size)
{
	_appCmd.size = size;
}

void L6470MotorData::setAppValue(int val, int appCmd)
{
	// todo: confirm & compare with previous calc
	uint32_t optimizedValue;

	switch(appCmd)
	{
		// convert from rps
		case RUN :
		case GOUNTIL :
		{
			optimizedValue = (uint32_t)((double)(abs(val))/(double)SPD_RES_COMMAND);
			break;
		}
		// convert from step
		case MOVE :
		{
			optimizedValue = (uint32_t)((double)(abs(val))*(double)pow(2, _microStep));
			break;
		}
		// convert from angle
		case GOTO :
		case GOTO_DIR :
		{
			optimizedValue = (uint32_t)((double)_motorStep*(double)pow(2, _microStep)*(double)val/360.0);
			break;
		}
		default:
		{
			optimizedValue = (uint32_t)abs(val);
			break;
		}
	}
	_appCmd.value = optimizedValue;
}

void L6470MotorData::setRegCmd(int cmd)
{
	_regCmd.cmd = cmd;
}

void L6470MotorData::setRegSize(int size)
{
	_regCmd.size = size;
}

void L6470MotorData::setRegValue(int val, int reg)
{
	// todo: confirm & compare with previous calc
	uint32_t optimizedValue;

	switch(reg)
	{
		// convert from speed
		case REG_MAX_SPEED:
		{
			_curRps = val;
			optimizedValue = (uint32_t)((float)val/(float)SPD_RES_LIMIT);
			break;
		}
		case REG_MIN_SPEED:
		{
			optimizedValue = (uint32_t)((float)val/(float)SPD_RES_LIMIT);
			break;
		}
		default:
		{
			optimizedValue = val;
			break;
		}
	}
	_regCmd.value = optimizedValue;
}


uint8_t L6470MotorData::getAppCmd()
{
	return (uint8_t)_appCmd.cmd;
}

uint8_t L6470MotorData::getAppSize()
{
	return (uint8_t)_appCmd.size;
}

uint32_t L6470MotorData::getAppValue()
{
	return (uint32_t)_appCmd.value;
}

uint8_t L6470MotorData::getRegCmd()
{
	return (uint8_t)_regCmd.cmd;
}

uint8_t L6470MotorData::getRegSize()
{
	return (uint8_t)_regCmd.size;
}

uint32_t L6470MotorData::getRegValue()
{
	return (uint32_t)_regCmd.value;
}

int	L6470MotorData::getCurRps()
{
	return _curRps;
}
