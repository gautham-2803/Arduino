
int sensorValue;
int incomingByte;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
 // pinMode(ledpin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop(){
     
      //  incomingByte = Serial.read();
      
           //   if (incomingByte == 'L'){
             // Serial.println(incomingByte);
              sensorValue = analogRead(A0);
              int smap = map(sensorValue,0,722,0,499); // mapping light sensor values from 0 - 722 to 1 - 10
              Serial.println(String(smap)); // Writing values on Serial port
              //delay(30000);
           //   } //incoming Byte
      //available
}
