#include "Setup.h"
void motor (String a , int x=255,int y=255);
void shut ();
long cmps ();
void cmpss ();


void setup() {

  pinMode(xshutPin, OUTPUT);
  digitalWrite(xshutPin, LOW);

  delay(10);

  pinMode(xshutPin2, OUTPUT);
  digitalWrite(xshutPin2, LOW);

  delay(10);

  pinMode(xshutPin3, OUTPUT);
  digitalWrite(xshutPin3, LOW);

  Serial.begin(115200);
  Wire.begin();

  digitalWrite(xshutPin, HIGH);
  delay(10);
  sensor.init();
  sensor.setTimeout(200);
  sensor.setAddress((uint8_t)48);
  delay(10);

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif

  digitalWrite(xshutPin2, HIGH);
  delay(10);
  sensor2.init();
  sensor2.setTimeout(200);
  sensor2.setAddress((uint8_t)49);
  delay(10);

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor2.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor2.setMeasurementTimingBudget(200000);
#endif
digitalWrite(xshutPin3, HIGH);
  delay(10);
  sensor3.init();
  sensor3.setTimeout(200);
  sensor3.setAddress((uint8_t)50);
  delay(10);

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor2.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor2.setMeasurementTimingBudget(200000);
#endif
Serial.begin(115200);
Wire.begin();
cmps11 = cmps();
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
// ............................"" vl-53 ""
pinMode(fms, INPUT);
pinMode(rfs, INPUT);
pinMode(rbs, INPUT);
pinMode(lfs, INPUT);
pinMode(lbs, INPUT);
// pinMode(brs, INPUT);
// pinMode(bls, INPUT);

// ............................"" motors ""
pinMode(enA, OUTPUT);  
pinMode(enB, OUTPUT); 
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);  
// pinMode(in3, OUTPUT);  
// pinMode(in4, OUTPUT);


}
void loop() {
  Serial.println(sensor.readRangeSingleMillimeters());
  while(sensor.readRangeSingleMillimeters()>150){
    Serial.println(sensor.readRangeSingleMillimeters());
    motor("forward");

    // if (rf() > lf()){
    //   motor( "forward" ,100,255);  
    // }

    // if (lf() > rf()){
    //   motor( "forward" , 255,100);
        
    // }
  }
  motor("stop");
delay(1000);
if (sensor.readRangeSingleMillimeters()<150){
    
      cmps11=cmps();
    if (3>2){
      while (true){
        xc = abs(cmps() - (cmps11 + 90));
        if (xc < 0){
          xc = xc*-1;
        }
        if (xc > 360){
          cmps11 = 0-360+cmps11;
        }
        motor("left",130,130);
        Serial.print("cmps:  ");
        Serial.print(cmps());
        Serial.print("  cmps11:  ");
        Serial.print(cmps11);
        Serial.print("  xc :  ");
        Serial.println(xc);
          if (xc<90 ){
          break;
          }
    // motor("stop");
    }
  
}
}      
}


//--------------------------------   Functuin ------------------------------
int getBearing()
{
  // begin communication with CMPS11
  Wire.beginTransmission(_i2cAddress);

  // Tell register you want some data
  Wire.write(BEARING_REGISTER);

  // End transmission
  int nackCatcher = Wire.endTransmission();

  // Return if we have a connection problem  
  if(nackCatcher != 0){return 0;}
  
  // Request 2 bytes from CMPS11
  nReceived = Wire.requestFrom(_i2cAddress , TWO_BYTES);

  // Something has gone wrong
  if (nReceived != TWO_BYTES) return 0;
  
  // Read the values
  _byteHigh = Wire.read(); 
  _byteLow = Wire.read();

  // Calculate full bearing
  bearing = ((_byteHigh<<8) + _byteLow) / 10;
  
  return bearing;
}
int16_t getAcceleroX()
{
  // Begin communication with CMPS11
  Wire.beginTransmission(_i2cAddress);

  // Tell register you want some data
  Wire.write(ACCEL_X_REGISTER);

  // End the transmission
  int nackCatcher = Wire.endTransmission();

  // Return if we have a connection problem 
  if(nackCatcher != 0){return 0;}
  
  // Request 2 bytes from CMPS11
  nReceived = Wire.requestFrom(_i2cAddress , TWO_BYTES);

  // Something has gone wrong
  if (nReceived != TWO_BYTES) return 0;

  // Read the values
  _byteHigh = Wire.read(); 
  _byteLow = Wire.read();

  // Calculate Accelerometer
  return (((int16_t)_byteHigh <<8) + (int16_t)_byteLow);
}
long cmps (){
   bearing = getBearing();
  
  // Read the accelerator
  accelx = getAcceleroX() * _accelScale;
  return (bearing);
}
void cmpss (){
   bearing = getBearing();
  
  // Read the accelerator
  accelx = getAcceleroX() * _accelScale;
  Serial.println(bearing);
}


void motor (String a , int x=255,int y=255){
if (a == "forward"){
 digitalWrite(in1, LOW);

 digitalWrite(in2, HIGH);

 digitalWrite(in3, LOW);

 digitalWrite(in4, HIGH);

 analogWrite(enA, x); 

 analogWrite(enB, y);
}

if (a == "backward"){
 digitalWrite(in1, HIGH);

 digitalWrite(in2, LOW);

 digitalWrite(in3, HIGH);

 digitalWrite(in4, LOW);

 analogWrite(enA, x); 

 analogWrite(enB, y);
}

if (a == "right"){
 digitalWrite(in1, HIGH);

 digitalWrite(in2, LOW);

 digitalWrite(in3, LOW);

 digitalWrite(in4, HIGH);

 analogWrite(enA, x); 

 analogWrite(enB, y);
}

if (a == "left"){
 digitalWrite(in1, LOW);

 digitalWrite(in2, HIGH);

 digitalWrite(in3, HIGH);

 digitalWrite(in4, LOW);

 analogWrite(enA, x); 

 analogWrite(enB, y);
}

if (a == "stop"){
 digitalWrite(in1, LOW);

 digitalWrite(in2, LOW);

 digitalWrite(in3, LOW);

 digitalWrite(in4, LOW);

 analogWrite(enA, x); 

 analogWrite(enB, y);
}
}
void shut (){
  pinMode(xshutPin, OUTPUT);
  digitalWrite(xshutPin, LOW);

  delay(10);

  pinMode(xshutPin2, OUTPUT);
  digitalWrite(xshutPin2, LOW);

  delay(10);

  pinMode(xshutPin3, OUTPUT);
  digitalWrite(xshutPin3, LOW);

  Serial.begin(115200);
  Wire.begin();

  digitalWrite(xshutPin, HIGH);
  delay(10);
  sensor.init();
  sensor.setTimeout(200);
  sensor.setAddress((uint8_t)48);
  delay(10);

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif

  digitalWrite(xshutPin2, HIGH);
  delay(10);
  sensor2.init();
  sensor2.setTimeout(200);
  sensor2.setAddress((uint8_t)49);
  delay(10);

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor2.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor2.setMeasurementTimingBudget(200000);
#endif
digitalWrite(xshutPin3, HIGH);
  delay(10);
  sensor3.init();
  sensor3.setTimeout(200);
  sensor3.setAddress((uint8_t)50);
  delay(10);

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor2.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor2.setMeasurementTimingBudget(200000);
#endif
}

// int ultra(){ 
  
//   digitalWrite(trig, LOW); 
//   delayMicroseconds(2);
//   // Sets the trigPin on HIGH state for 10 micro seconds
//   digitalWrite(trig, HIGH); 
//   delayMicroseconds(10);
//   digitalWrite(trig, LOW);
//   durationj = pulseIn(echo, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
//   distancej= durationj*0.034/2*10;
//   return (distancej);
//  }

