// ............................"" library ""
#include <Temperature_LM75_Derived.h>
#include <Wire.h>
#include <VL53L0X.h>



// ............................"" ultra ""
unsigned long durationj;
int distancej;
const int trig = 24;
const int echo = 22;

// ............................"" vl-53 ""

VL53L0X sensor;
VL53L0X sensor2;
VL53L0X sensor3;

const int xshutPin = 4;
const int xshutPin2 = 3;
const int xshutPin3 = 2;

#define fms  A0
#define rfs  A1
#define rbs  A5
#define lfs  A3
#define lbs  A6
// #define brs  A5
// #define bls  A6

// ............................"" **** ""
 String jahat[2] = {"left" , "right"};
int cmps11;
int fmt;
int x = 0 ;
int y = 0;
int xb;
int xf;
int xc;
int bmt = 0;

// ............................"" motors ""
#define enA  A8
#define in1  52
#define in2  50
#define enB  A9
#define in3  48
#define in4  46
#define PWM = 200;

// ............................"" lm75 ""
Generic_LM75 LM75;

// ............................"" lm75 ""
  #define _i2cAddress 0x60

  // CMPS11 compass registers
  #define BEARING_REGISTER  2 
  #define PITCH_REGISTER    4 
  #define ROLL_REGISTER     5
  
  #define ACCEL_X_REGISTER 12
  #define ACCEL_Y_REGISTER 14
  #define ACCEL_Z_REGISTER 16
  
  #define GYRO_X_REGISTER  18
  #define GYRO_Y_REGISTER  20
  #define GYRO_Z_REGISTER  22

  #define TEMP_REGISTER    24

  #define CONTROL_REGISTER  0

  #define ONE_BYTE 1
  #define TWO_BYTES 2

//---------------------------------

  int bearing;
  int nReceived;
  byte _fine;
  byte _byteHigh;
  byte _byteLow;
  char _pitch;
  char _roll;

  float accelx = 0;
  float accely = 0;
  float accelz = 0;
  float _accelScale = 9.80665f * 2.0f/32768.0f; // setting the accel scale to 2G. Gravity = 9.80665 m/s^2


