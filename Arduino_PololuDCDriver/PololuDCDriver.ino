#include "Arduino.h"
#include "ArduinoJson.h"
#include "libs/DualMC33926MotorShield.h"
#include "MotorData.h"
#include "MotorModel.h"


DualMC33926MotorShield driver(
		26, A0,
		28, A1,
		24, A2,

		30, 31,
		32, 33);
MotorData motor1(44, 42);
MotorModel model1(&motor1);

MotorData motor2(48, 46);
MotorModel model2(&motor2);

MotorData motor3(52, 50);
MotorModel model3(&motor3);


constexpr int BUFFER_SIZE = 100;

constexpr int WRITE_TIMEOUT = 50;
unsigned long writeTimer = 0;

void read_json();
void write_to_device();
int8_t canWriteToDevice();

void setup() {
	Serial.begin(115200);
	driver.init();

	motor1.init();
	motor2.init();
	motor3.init();

	pinMode(13, OUTPUT);

	while(!Serial);
	writeTimer = millis();
}

// MAIN LOOP START =======================
void loop() {

	if(Serial.available() > 0)
		read_json();

	if(driver.getFaultDriver1()) driver.resetDriver1();
	if(driver.getFaultDriver2()) driver.resetDriver2();


	motor1.readLimitSwitchesState();
	motor2.readLimitSwitchesState();
	motor3.readLimitSwitchesState();

	model1.computePwm();
	model2.computePwm();
	model3.computePwm();


	driver.setM1Speed(motor1.getPwm());
	driver.setM2Speed(motor2.getPwm());
	driver.setM3Speed(motor3.getPwm());

	if(canWriteToDevice())
		write_to_device();
}
// MAIN LOOP STOP  =======================


void read_json()
{
	auto data = Serial.readStringUntil('\n');
	StaticJsonBuffer<BUFFER_SIZE> buffer;
	JsonObject &root = buffer.parseObject(data);

	motor1.setPwm(root["mot1"]);
	motor2.setPwm(root["mot2"]);
	motor3.setPwm(root["mot3"]);

	digitalWrite(13, motor1.getPwm() > 0 ? HIGH : LOW);
}

void write_to_device()
{
	DynamicJsonBuffer jsonBuffer;
	JsonObject &root = jsonBuffer.createObject();
	root["mot1"] = motor1.getPwm();
	root["cu1"] = driver.getM1CurrentMilliamps();
	if(model1.isHalted() != 0)
		root["h1"] = model1.isHalted();

	root["mot2"] = motor2.getPwm();
	root["cu2"] = driver.getM2CurrentMilliamps();
	if(model2.isHalted() != 0)
		root["h2"] = model2.isHalted();

	root["mot3"] = motor3.getPwm();
	root["cu3"] = driver.getM3CurrentMilliamps();
	if(model3.isHalted() != 0)
		root["h3"] = model3.isHalted();

	root["err1"] = driver.getFaultDriver1();
	root["err2"] = driver.getFaultDriver2();
	root.printTo(Serial);
	Serial.print("\r\n");
}

int8_t canWriteToDevice()
{
	if(WRITE_TIMEOUT <= millis() - writeTimer)
	{
		writeTimer = millis();
		return 1;
	}
	return 0;
}
