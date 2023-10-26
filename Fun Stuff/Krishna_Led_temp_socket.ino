
#include <math.h> //include the math library
const int B = 4275;
String incomingByte;
int sensorValue;
const int R0 = 100000;
const int ledpin = 3;
String command1 ="TEMP\n";
String command2 ="LED 1\n";
String command3 ="LED 0\n";
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
}
// the loop routine runs over and over again forever:
void loop(){

        if (Serial.available() >0){
      
          incomingByte = Serial.readString();
          if (incomingByte == command3) {
                digitalWrite(ledpin,LOW);
                Serial.println("Led is off");

          }//command3
           else if (incomingByte == command2){
              digitalWrite(ledpin,HIGH);
              Serial.println("Led is on");
            }//command 2
           else if (incomingByte == command1) {
            float temp_c = read_temp();
             Serial.println(temp_c);              
          }
          }//Serial.available
}//loop

float read_temp(){ //function to read temperature.
      sensorValue = analogRead(A0); // Analog pin holds Temperature Sensor
  
      float R = 1023.0/sensorValue-1.0;
      R = R0 * R;
      float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15;// Temperature converted from sensor value to Fahrenheit.
    
      return temperature;

}

 