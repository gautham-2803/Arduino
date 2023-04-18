/*
  ADXL3xx

  Reads an Analog Devices ADXL3xx accelerometer and communicates the
  acceleration to the computer. The pins used are designed to be easily
  compatible with the breakout boards from SparkFun, available from:
  https://www.sparkfun.com/categories/80

  The circuit:
  - analog 0: accelerometer self test
  - analog 1: z-axis
  - analog 2: y-axis
  - analog 3: x-axis
  - analog 4: ground
  - analog 5: vcc

  created 2 Jul 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ADXL3xx
*/
#include <Wire.h>
#include <ADXL345.h>

ADXL345 adxl;

// these constants describe the pins. They won't change:
const int groundpin = 18;  // analog input pin 4 -- ground
const int powerpin = 19;   // analog input pin 5 -- voltage
const int xpin = A3;       // x-axis of the accelerometer
const int ypin = A2;       // y-axis
const int zpin = A1;       // z-axis (only on 3-axis models)
const int GSR = A2;
int sensorValue = 0;
int gsr_average = 0;

int PulseSensorPurplePin = A1;  // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED = LED_BUILTIN;          //  The on-board Arduion LED


int Signal;  // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 450;

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
  adxl.powerOn();
  // Provide ground and power by using the analog inputs as normal digital pins.
  // This makes it possible to directly connect the breakout board to the
  // Arduino. If you use the normal 5V and GND pins on the Arduino,
  // you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);

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
}

void loop() {
  double xyz[3];
  double ax, ay, az;
  adxl.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];
  // Serial.print("X=");
  // Serial.print(ax);
  // Serial.println(" g");
  // Serial.print("Y=");
  // Serial.print(ay);
  // Serial.println(" g");
  // Serial.print("Z=");
  // Serial.print(az);
  // Serial.println(" g");
  // Serial.println("**********************");
  // delay(1000);


  long sum = 0;
  for (int i = 0; i < 10; i++)  //Average the 10 measurements to remove the glitch
  {
    sensorValue = analogRead(GSR);
    sum += sensorValue;
    // delay(5);
  }
  gsr_average = sum / 10;
  // Serial.println("gsr value "+String(gsr_average));
  // Serial.println(gsr_average);
  // delay(100);
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.

  Serial.println(Signal);  // Send the Signal value to Serial Plotter.


  if (Signal > Threshold) {  // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);  //  Else, the sigal must be below "550", so "turn-off" this LED.
  }


  delay(20);
}
