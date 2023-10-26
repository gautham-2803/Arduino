#include <Grove_LED_Bar.h>
#define NUM_OF_LED 24
Grove_LED_Bar LEDbar(0,1,0,LED_CIRCULAR_24); //clock pin, data pin, orientation


void setup() {
  // put your setup code here, to run once:
  LEDbar.begin();

}

void loop() {
//brightness level

  LEDbar.setGreenToRed(0);
  for(float i=0;i<24;i+=.125f){
    LEDbar.setLevel(i);
    delay(25);
  }

  for(float i=0;i<24;i+=.125f){
    LEDbar.setLevel(24-i);
    delay(25);
  }

LEDbar.setGreenToRed(1);
  for(float i=0;i<24;i+=.125f){
    LEDbar.setLevel(i);
    delay(25);
  }

  for(float i=0;i<24;i+=.125f){
    LEDbar.setLevel(24-i);
    delay(25);
  }


// // police siren
//   for (float i=0;i<1.1; i+=.125f){
//     LEDbar.setLed(1, i);
//     LEDbar.setLed(2, i);
//     LEDbar.setLed(3, 1-i);
//     LEDbar.setLed(4, 1-i);
//     delay(150);
//   }

//   for (float i=0;i<1.1; i+=.125f){
//     LEDbar.setLed(1, 1-i);
//     LEDbar.setLed(2, 1-i);
//     LEDbar.setLed(3, i);
//     LEDbar.setLed(4, i);
//     delay(150);
//   }

  
 // start clockwise

  // for(int i = 0; i<=NUM_OF_LED; i++){
  //   LEDbar.setLevel(i);
  //   delay(200);
  // }

  // LEDbar.setLevel(0);

  // //anticlock wise
  // LEDbar.setGreenToRed(1);
  // for(int i = 0; i<=NUM_OF_LED; i++){
  //   LEDbar.setLevel(i);
  //   delay(200);
  // }


  // LEDbar.setLevel(0);

  // //Clock wise
  // LEDbar.setGreenToRed(0);

  // for(int i = 1; i<=NUM_OF_LED; i++){
  //   LEDbar.setLevel(i);
  //   delay(500);

  //   LEDbar.setGreenToRed(1);
  //   delay(500);

  //   LEDbar.setGreenToRed(0);

  // }
  // LEDbar.setLevel(0);
  // //turn all on 
  // LEDbar.setLevel(24);
  // delay(1000);

  // //turn off led 3
  // LEDbar.toggleLed(3);
  // delay(1000);

  // //turn on led 3
  // LEDbar.toggleLed(3);
  // delay(1000);

  // //turn all off 
  // LEDbar.setLevel(0);
  // delay(1000);

  // //turn on led 3
  // LEDbar.toggleLed(7);
  // delay(1000);

  // //turn off led 3
  // LEDbar.toggleLed(7);
  // delay(1000);




  //walk through the leds

  // for(int i = 0; i<=NUM_OF_LED; i++){
  //   LEDbar.setLevel(i);
  //   delay(100);
  // }
  /*
  // turn first 10 leds
  LEDbar.setBits(0x3ff);
  delay(1500);
  
  //turn off all
  LEDbar.setBits(0x0);
  delay(1500);
  
  //turn on just the first
  
  LEDbar.setBits(0b000000000000001); // or 0x1
  delay(1500);

  //turn on 1 and 3
  LEDbar.setBits(0b000000000000101); // or 0x5
  delay(1500);

  // tun on 1,3,5,7,9

  LEDbar.setBits(0b000000101010101); // or 0x155
  delay(1500);
  //tun on 2,4,6,8,10
  LEDbar.setBits(0x2AA); // or 0x155
  delay(1500);

  //tun on 1,2,3,4,5
  LEDbar.setBits(0b000000000011111); // or 0x155
  delay(1500);

  
  //tun on 6,7,8,9,10
  LEDbar.setBits(0b000001111100000); // or 0x155
  delay(1500);

  //turn on 11-17

  LEDbar.setBits(0b000000011111110000000000); 
  delay(1500);
  //turn on 18-24

  LEDbar.setBits(0b111111100000000000000000); 
  delay(1500);

  //turn on odd numbers 1-23

 

  LEDbar.setBits(0b010101010101010101010101); // or 0x1
  delay(1500);

  //turn on even numbers 0-24
  LEDbar.setBits(0b101010101010101010101010); // or 0x1
  delay(1500);
  
  //turn on odd numbers 1-23

 

  LEDbar.setBits(0x0555555); // or 0x1
  delay(1500);

  //turn on even numbers 0-24

  LEDbar.setBits(0x0AAAAAA); // or 0x1
  delay(1500);
  
   */
}
