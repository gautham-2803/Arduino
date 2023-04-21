#include <Wire.h>
#include <ADXL345.h>
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

const int GSR = A2;
int sensorValue = 0;
int gsr_average = 0;
const int PulseWire = 1;
int Threshold = 550;

ADXL345 adxl;
PulseSensorPlayground pulseSensor;

void setup() {
  Serial.begin(9600);
  adxl.powerOn();

  adxl.setActivityThreshold(75);    //62.5mg per increment
  adxl.setInactivityThreshold(75);  //62.5mg per increment
  adxl.setTimeInactivity(10);       // how many seconds of no activity is inactive?

  //look of activity movement on this axes - 1 == on; 0 == off
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);

  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);

  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);

  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50);      //62.5mg per increment
  adxl.setTapDuration(15);       //625us per increment
  adxl.setDoubleTapLatency(80);  //1.25ms per increment
  adxl.setDoubleTapWindow(200);  //1.25ms per increment

  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7);  //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45);  //(20 - 70) recommended - 5ms per increment

  //setting all interrupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping(ADXL345_INT_SINGLE_TAP_BIT, ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_DOUBLE_TAP_BIT, ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_FREE_FALL_BIT, ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_ACTIVITY_BIT, ADXL345_INT1_PIN);
  adxl.setInterruptMapping(ADXL345_INT_INACTIVITY_BIT, ADXL345_INT1_PIN);

  //register interrupt actions - 1 == on; 0 == off
  adxl.setInterrupt(ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt(ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt(ADXL345_INT_FREE_FALL_BIT, 1);
  adxl.setInterrupt(ADXL345_INT_ACTIVITY_BIT, 1);
  adxl.setInterrupt(ADXL345_INT_INACTIVITY_BIT, 1);

  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
}

void loop() {
  long sum = 0;
  double xyz[3];
  double ax, ay, az;
  adxl.getAcceleration(xyz);
  ax = abs(xyz[0]);
  ay = abs(xyz[1]);
  az = abs(xyz[2]);
  // ax = random(1,5);
  // ay = random(1,5);
  // az = random(1,6);

  for (int i = 0; i < 10; i++)  //Average the 10 measurements to remove the glitch
  {
    sensorValue = analogRead(GSR);
    // sensorValue = random(200,500);
    sum += sensorValue;
    delay(5);
  }
  gsr_average = sum / 10;

  // if (pulseSensor.sawStartOfBeat()) {
  //   // int BPM = pulseSensor.getBeatsPerMinute();
  // }

  int BPM = random(60, 80);

  Serial.print(gsr_average);
  Serial.print(" ");
  Serial.print(BPM);
  Serial.print(" ");
  Serial.print(ax);
  Serial.print(" ");
  Serial.print(ay);
  Serial.print(" ");
  Serial.println(az);

  delay(800);
}
