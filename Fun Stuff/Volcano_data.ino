#include <Grove_LED_Bar.h>
Grove_LED_Bar bar(7, 6, 1, LED_BAR_10); // Clock pin, Data pin, Orientation

String COM_VOLCANO_LEVEL = "COM_VOLCANO_LEVEL\n";
//String ACK_VOLCANO_LEVEL = "ACK_VOLCANO_LEVEL"; //only for ack string

void setup(){
  Serial.begin( 115200 );
  bar.begin();
}

void loop(){
  if (Serial.available() > 0){  // Check if there is data available to read from the Serial port.
    String s_com = (Serial.readStringUntil("/r"));
   
    if(s_com == COM_VOLCANO_LEVEL){
      //Serial.println(ACK_VOLCANO_LEVEL); //ack string
      while(1){
        if (Serial.available() > 0){  // Check if there is data available to read from the Serial port.
          String s_level = Serial.readString();
          int level = s_level.toInt();
          int mapped_value = map(level, 0, 5, 1, 10);
          bar.setLevel(mapped_value);
          delay(100);
          //Serial.println(ACK_VOLCANO_LEVEL);
          break; 
        }
      }
    }
  }
}
