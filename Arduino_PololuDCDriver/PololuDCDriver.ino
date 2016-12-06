#include "Arduino.h"
#include "ArduinoJson.h"
#include "libs/DualMC33926MotorShield.h"
#include "MotorData.h"
#include "MotorModel.h"


DualMC33926MotorShield driver1(26, 2, A0, 28, 3, A1, 30, 31);
MotorData motor1(44, 42);
MotorModel model1(&motor1);

MotorData motor2(48, 46);
MotorModel model2(&motor2);

MotorData motor3(52, 50);
MotorModel model3(&motor3);


constexpr int BUFFER_SIZE = 100;

void read_json();
void write_to_device();


void setup() {
	Serial.begin(115200);
	driver1.init();

	motor1.init();
	motor2.init();
	motor3.init();

	pinMode(13, OUTPUT);

	while(!Serial);
}

// MAIN LOOP START =======================
void loop() {

	if(Serial.available() > 0)
		read_json();

	motor1.readLimitSwitchesState();
	motor2.readLimitSwitchesState();
	motor3.readLimitSwitchesState();

	driver1.setM1Speed(model1.getPwm());

	write_to_device();
	delay(50);
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
	root["m1ls"] = motor1.getCounterClockwisePinState();
	root["m1rs"] = motor1.getClockwisePinState();
	root["cu1"] = driver1.getM1CurrentMilliamps();
	if(model1.isHalted() != 0)
		root["h1"] = model1.isHalted();

	root["mot2"] = motor2.getPwm();
	root["m2ls"] = motor2.getCounterClockwisePinState();
	root["m2rs"] = motor2.getClockwisePinState();
	if(model2.isHalted() != 0)
		root["halt2"] = model2.isHalted();

	root["mot3"] = motor3.getPwm();
	root["m3ls"] = motor3.getCounterClockwisePinState();
	root["m3rs"] = motor3.getClockwisePinState();
	if(model3.isHalted() != 0)
		root["h3"] = model3.isHalted();

	root.printTo(Serial);
	Serial.print("\r\n");
}
