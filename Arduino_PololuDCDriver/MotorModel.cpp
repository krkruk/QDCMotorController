/*
 * MotorModel.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: krzysztof
 */

#include "MotorModel.h"

MotorModel::MotorModel(MotorData* motor)
	: _motor(motor)
{
}

void MotorModel::computePwm()
{
	int pwm = _motor->getPwm();
	_direction = getDirection(pwm);
	_isHalted = 0;

	switch(_direction)
	{
	case CLOCKWISE:
		if(_motor->getClockwisePinState()){
			_isHalted = CLOCKWISE;
			pwm = 0;
		}
		break;
	case COUNTERCLOCKWISE:
		if(_motor->getCounterClockwisePinState()) {
			_isHalted = COUNTERCLOCKWISE;
			pwm = 0;
		}
		break;
	case 0:
	default:
		if(_motor->getClockwisePinState()) _isHalted = CLOCKWISE;
		if(_motor->getCounterClockwisePinState()) _isHalted = COUNTERCLOCKWISE;
		pwm = 0;
		break;
	}

	if(_motor->getClockwisePinState()
			&& _motor->getCounterClockwisePinState()) {
		_isHalted = WTF;
		pwm = 0;
	}

	_motor->setPwm(pwm);
}

int8_t MotorModel::getDirection(const int& pwm)
{
	return pwm > 0 ? CLOCKWISE :
			pwm < 0 ? COUNTERCLOCKWISE : 0;
}
