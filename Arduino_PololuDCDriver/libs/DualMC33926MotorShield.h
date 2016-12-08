#ifndef DualMC33926MotorShield_h
#define DualMC33926MotorShield_h

#include <Arduino.h>

class DualMC33926MotorShield
{
  public:  
    DualMC33926MotorShield(uint8_t M1DIR, uint8_t M1FB,
    					   uint8_t M2DIR, uint8_t M2FB,
						   uint8_t M3DIR, uint8_t M3FB,
                           uint8_t D1nD2, uint8_t D1nSF,
						   uint8_t D2nD2, uint8_t D2nSF); // User-defined pin selection.
    
    // PUBLIC METHODS
    void init(); // Initialize TIMER 1, set the PWM to 20kHZ. 
    void setM1Speed(int speed); // Set speed for M1.
    void setM2Speed(int speed); // Set speed for M2.
    void setM3Speed(int speed);
    void setSpeeds(int m1Speed, int m2Speed, int m3Speed); // Set speed for all motors

    unsigned int getM1CurrentMilliamps(); // Get current reading for M1. 
    unsigned int getM2CurrentMilliamps(); // Get current reading for M2.
    unsigned int getM3CurrentMilliamps(); // Get current reading for M3.

    unsigned char getFaultDriver1(); // Get fault reading of driver1
    unsigned char getFaultDriver2(); // Get fault reading of driver1
    
  private:
    uint8_t _D1nD2;
    uint8_t _M1DIR;
    uint8_t _M2DIR;

    static const uint8_t _M1PWM = 6;
    static const uint8_t _M2PWM = 7;

    uint8_t _D1nSF;
    uint8_t _M1FB;
    uint8_t _M2FB;

    //driver2
    uint8_t _D2nD2;
    uint8_t _D2nSF;
    static const uint8_t _M3PWM = 8;
    uint8_t _M3DIR;
    uint8_t _M3FB;
};

#endif
