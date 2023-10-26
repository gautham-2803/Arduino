#include <ctype.h>
#include <Grove_LED_Bar.h>
#include <Servo.h>

//  setting up servo and LED Bar

Grove_LED_Bar bar(7,6, 1, LED_BAR_10);
Servo myServo;

int led_level =1;

// defining constants for levels 

const int MID = 5;
const int DOWN = 1;
const int UP = 10;

// defining variable to go to initial position 
int servo_pos = 30;

String command1 = "MID\n";
String command2 = "UP\n";
String command3 = "DOWN\n";
String command4_start = "SLAT ";

//  function to raise or lower the blinds

void raiseOrlower(int level, int pos){
  myServo.write(90);
  delay(1000);
  bar.setLevel(level);
  delay(1000);
  myServo.write(pos);
}

int digitsOnly(const char *s){
  while(*s){
    if (isDigit(*s++) == 0) return 0;
  }
  return 1;
}


void setup() {
  Serial.begin(9600);
  myServo.attach(2);
  bar.begin();
  bar.setGreenToRed(false);
  raiseOrlower(led_level, servo_pos);

  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available()>0){
    String command = Serial.readString();
    if(command == command1){
      raiseOrlower(MID, servo_pos);
      Serial.println("MID");
    }
    else if(command == command2){
      raiseOrlower(UP, servo_pos);
      Serial.println("UP");
    }// command 2
     else if(command == command3){
      raiseOrlower(DOWN, servo_pos);
      Serial.println("DOWN");
    }// command 3
    else if ( command.startsWith(command4_start)){
      String str_pos = command.substring(5,command.length()-1);
      if ( str_pos.length() >= 1 && digitsOnly(str_pos.c_str())){
        servo_pos = map(str_pos.toInt(), 0, 100, 0, 180); // mapping this from numbers to Degree
        myServo.write(servo_pos);
        Serial.println(servo_pos);

      } // str_pos length and validation 
      else {
        Serial.print("BAD POSITION");
      }
    }
    else {
      Serial.println("Bad command");
    }
  }// Serial. available
}
