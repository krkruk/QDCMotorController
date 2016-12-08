#include "DualMC33926MotorShield.h"


DualMC33926MotorShield::DualMC33926MotorShield(
		uint8_t M1DIR, uint8_t M1FB,
		uint8_t M2DIR, uint8_t M2FB,
		uint8_t M3DIR, uint8_t M3FB,
        uint8_t D1nD2, uint8_t D1nSF,
		uint8_t D2nD2, uint8_t D2nSF)
{
	//in driver1
	//init motor1
	_M1DIR = M1DIR;
	_M1FB = M1FB;

	//init motor2
	_M2DIR = M2DIR;
	_M2FB = M3FB;

	//state pins
	_D1nD2 = D1nD2;
	_D1nSF = D1nSF;

	//in driver2
	//init motor3
	_M3DIR = M3DIR;
	_M3FB = M3FB;

	//state pins
	_D2nD2 = D2nD2;
	_D2nSF = D2nSF;
}

// Public Methods //////////////////////////////////////////////////////////////
void DualMC33926MotorShield::init()
{
// Define pinMode for the pins and set the frequency for timer1.

	//driver1
	//setup motor1
	pinMode(_M1DIR,OUTPUT);
	pinMode(_M1FB,INPUT);
	pinMode(_M1PWM,OUTPUT);

	//setup motor2
	pinMode(_M2DIR,OUTPUT);
	pinMode(_M2FB,INPUT);
	pinMode(_M2PWM,OUTPUT);

	//setup state pins
	pinMode(_D1nD2,OUTPUT);
	digitalWrite(_D1nD2,HIGH); // default to on
	pinMode(_D1nSF,INPUT);


	//driver2
	//setup motor3
	pinMode(_M3DIR, OUTPUT);
	pinMode(_M3FB, INPUT);
	pinMode(_M3PWM, OUTPUT);

	//setup state pins
	pinMode(_D2nD2, OUTPUT);
	digitalWrite(_D2nD2, HIGH);
	pinMode(_D2nSF, INPUT);


	TCCR4A = 1<<COM4A1 | 1<<COM4B1 | 1<<COM4C1	//enable pin
			| 1<<WGM40;	//phase an freq pwm(9), 20kHz PWM
	TCCR4B = 1<<WGM43;
	ICR4 = 400;
	OCR4A = 0;
	OCR4B = 0;
	OCR4C = 0;
	TCCR4B = 1<<CS40;
}
// Set speed for motor 1, speed is a number between -400 and 400
void DualMC33926MotorShield::setM1Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;

  OCR4A = speed * 51 / 80;

  if (reverse)
    digitalWrite(_M1DIR,HIGH);
  else
    digitalWrite(_M1DIR,LOW);
}

// Set speed for motor 2, speed is a number between -400 and 400
void DualMC33926MotorShield::setM2Speed(int speed)
{
  unsigned char reverse = 0;
  
  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;

  OCR4B = speed * 51 / 80;

  if (reverse)
    digitalWrite(_M2DIR,HIGH);
  else
    digitalWrite(_M2DIR,LOW);
}

void DualMC33926MotorShield::setM3Speed(int speed)
{
  unsigned char reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // Make speed a positive quantity
    reverse = 1;  // Preserve the direction
  }
  if (speed > 400)  // Max PWM dutycycle
    speed = 400;

  OCR4C = speed * 51 / 80;

  if (reverse)
    digitalWrite(_M3DIR,HIGH);
  else
    digitalWrite(_M3DIR,LOW);
}

// Set speed for motor 1 and 2
void DualMC33926MotorShield::setSpeeds(int m1Speed, int m2Speed, int m3Speed)
{
  setM1Speed(m1Speed);
  setM2Speed(m2Speed);
  setM3Speed(m3Speed);
}

// Return motor 1 current value in milliamps.
unsigned int DualMC33926MotorShield::getM1CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  return analogRead(_M1FB) * 9;
}

// Return motor 2 current value in milliamps.
unsigned int DualMC33926MotorShield::getM2CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  return analogRead(_M2FB) * 9;
}

// Return motor 3 current value in milliamps.
unsigned int DualMC33926MotorShield::getM3CurrentMilliamps()
{
  // 5V / 1024 ADC counts / 525 mV per A = 9 mA per count
  return analogRead(_M3FB) * 9;
}

// Return error status
unsigned char DualMC33926MotorShield::getFaultDriver1()
{
  return !digitalRead(_D1nSF);
}

// Return error status
unsigned char DualMC33926MotorShield::getFaultDriver2()
{
  return !digitalRead(_D2nSF);
}
