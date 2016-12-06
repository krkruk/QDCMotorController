/*
 * Motor.cpp
 *
 *  Created on: Dec 6, 2016
 *      Author: krzysztof
 */

#include "MotorData.h"


MotorData::MotorData(uint8_t ccwisePin, uint8_t cwisePin)
	: _ccwisePin(ccwisePin), _cwisePin(cwisePin)
{
}

void MotorData::init()
{
	pinMode(_ccwisePin, INPUT_PULLUP);
	pinMode(_cwisePin, INPUT_PULLUP);
}

void MotorData::readLimitSwitchesState() {
	_ccwiseState = digitalRead(_ccwisePin);
	_cwiseState = digitalRead(_cwisePin);
}
