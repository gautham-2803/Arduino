#include <ctype.h>
#include <Servo.h>
#include <Grove_LED_Bar.h>

Grove_LED_Bar bar(7, 6, 1, LED_BAR_10);

Servo myservo;

float servo_pos = 90;

void setup() {
  Serial.begin(115200);
  myservo.attach(2);
  myservo.write(servo_pos);

  // put your setup code here, to run once:

}

boolean isValidNumber(String str){
  boolean isNum = false;
  for (byte i=0; i < str.length()-1; i++){
    isNum = isDigit(str.charAt(i)) || str.charAt(i)== '.';
    if (!isNum) return false;


  }//for
  return isNum;
}//isValid

void loop() {
  if(Serial.available() >0){
    String str_pos = Serial.readString();
    if (str_pos.length() >= 1 && isValidNumber(str_pos)){
      //convert the string to a number
      float servo_pos = str_pos.toFloat();
      Serial.println(servo_pos);
      myservo.write(servo_pos);


    }//valid string
    else {

    }

  }//serial.available

}//loop
