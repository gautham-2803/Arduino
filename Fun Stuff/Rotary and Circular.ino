#include <Grove_LED_Bar.h>


#define ROTARY_ANGLE_SENSOR A4 //battery chase right side port 1

#define NUM_OF_LED 24
Grove_LED_Bar LEDbar(0,1,0,LED_CIRCULAR_24); //wio terminal right of power cord



void setup() {

  pinMode(ROTARY_ANGLE_SENSOR,INPUT);
  LEDbar.begin();
  Serial.begin(9600);


}

void loop() {
  int light_level = getLightLevel();
  if(light_level){
   
    for(int i=1;i<=light_level;i++)
    { 
      LEDbar.setLed(i,1);
      delay(200);

    }}
   
    for (int j=NUM_OF_LED; j>light_level; j--){
      LEDbar.setLed(j,0);
      delay(200);
    }

  // }

}//loop

int getLightLevel(){
  int reading = analogRead(A4);
  int level = map(reading,0,1023,0,24);

  Serial.println(level);
  return level;
}
