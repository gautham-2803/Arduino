//use buttons for flashing
//use buttons for dip and dim
//use python to start
//use buzzer

//Pin Connections

// D0 - Motion Sensor
// D2 - Circular LED
// D4 - Ultrasound Ranger
// D6 - Temperature and Humidity Sensor 
// I2C Port - Digital Light Sensor
// WIO_KEY_B - Activates Temperature and Humidity Sensor 
// WIO_KEY_C - Activates Moption Sensor 
// WIO_5S_PRESS - Activates Low Beam and High Beam

//include files
#include <DHT.h>
#include <Ultrasonic.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <Digital_Light_TSL2561.h>
#include <Grove_LED_Bar.h>
#include <SoftwareSerial.h>


//defining constants
#define NUM_OF_LED 24
int speakerPin = WIO_BUZZER;
#define DHTTYPE DHT11
#define DHTPIN 6
#define MOTION_SENSOR 0
DHT dht(DHTPIN, DHTTYPE);
int frequency = 3000;
int light = 0;
bool x = true;

//setting up TFT

TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft);




void setup() {

  //To initialize all sensors to begin

  Wire.begin();
  Serial.begin(115200);
  TSL2561.init();
  dht.begin();
  digitalWrite(LCD_BACKLIGHT, LOW);
  tft.begin();
  tft.setRotation(3);
  pinMode(speakerPin, OUTPUT);
  pinMode(MOTION_SENSOR, INPUT);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT);
  Grove_LED_Bar LEDbar(2, 3, 0, LED_CIRCULAR_24);
}

void loop() {
  
   if (Serial.available() > 0)
  {
    String command = Serial.readString();
    Serial.println(command);

    if (command == "G")
    {
      getReadyMessage();
      startEngine();
    }
  }
  
  // getReadyMessage();
  // startEngine();

}
//This function is used to check the presence of an object to the right. It is useful while passing lanes. 
void checkRight() { 
  if (digitalRead(WIO_KEY_C) == LOW) {
    if (digitalRead(MOTION_SENSOR)) {
      Serial.println("Object");
      for (long i = 0; i < 1000 * 1000L; i += 1000 * 2) {
        digitalWrite(speakerPin, HIGH);

        delayMicroseconds(1915);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(1915);
      }
      // digitalWrite(speakerPin, HIGH);
      tft.fillScreen(TFT_RED);
      tft.setTextColor(TFT_WHITE);
      tft.setTextSize(3);
      tft.setCursor(50, 50);
      tft.drawString("Object!", 20, 30);
    } 
    // else {
    //   tft.fillScreen(TFT_WHITE);
    //   Serial.println("No Object");
    // }
  }
}

//This function is initially executed when there is a remote start command from the user. This simulates systems check and welcome address. 
void getReadyMessage() {
  tft.fillScreen(TFT_MAGENTA);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(3);
  tft.setCursor(50, 50);
  tft.drawString("All Systems Go!", 20, 30);
  delay(2000);
  tft.fillScreen(TFT_MAGENTA);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Welcome X", 20, 30);
  delay(2000);
}

//This function is executed second. This simulates engine start and checks the weather to give notification on it. 
void startEngine() {
  
  tft.fillScreen(TFT_MAGENTA);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(3);
  tft.setCursor(50, 50);
  tft.drawString("Engine Start!", 20, 30);
  delay(2000);
  float temp_hum_val[2] = { 0 };
  dht.readTempAndHumidity(temp_hum_val);
  Serial.println(temp_hum_val[1]);
  if (int(temp_hum_val[1]) < 20) {
    tft.fillScreen(TFT_YELLOW);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(3);
    tft.setCursor(50, 50);
    tft.drawString("Bad Weather!", 20, 50);
    tft.drawString("Drive Safe", 100, 80);
    delay(2000);
  } else {
    tft.fillScreen(TFT_BLUE);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(3);
    tft.setCursor(50, 50);
    tft.drawString("Beautiful Day!", 20, 30);
    delay(2000);
  }
  //All respective functions are called in a loop to ensure continuous monitoring. 
  while (x) {
    readAndLightFront();
    getTemperature();
    readUltrasonic();
    checkRight();
    
  }
}

//This functions turns on light sensor automatically based on the light value. On pressing WIO_5S_PRESS down, the light switches to low beam and high beam, to simulate passing. 
void readAndLightFront() {
  light = 0;
  Grove_LED_Bar LEDbar(2, 3, 0, LED_CIRCULAR_24);
  int light_value = TSL2561.readVisibleLux();
  // delay(1000);
  Serial.print(" Light value: ");
  Serial.println(light_value);
  // flag = 0;
  // Serial.println(x);
  if (light ==0){
    if (light_value < 50) {

      LEDbar.setLevel(24);

    } else {
      LEDbar.setLevel(0);
    }
  }
  if (digitalRead(WIO_5S_PRESS) == LOW) {
    light =1;
    LEDbar.setLevel(12);
    delay(300);
    LEDbar.setLevel(24);
    delay(300);
  }
  // delay(1000);
}

//this function is used to monitor engine temperature. This gets activated when you press WIO_KEY_B
void getTemperature() {
  if (digitalRead(WIO_KEY_B) == LOW) {
    float temp_hum_val[2] = { 0 };
    dht.readTempAndHumidity(temp_hum_val);
    Serial.println(temp_hum_val[1]);

    if (int(temp_hum_val[1]) <= 20) {
      tft.fillScreen(TFT_BLUE);
      tft.setTextColor(TFT_WHITE);
      tft.setTextSize(3);
      tft.setCursor(50, 50);
      tft.drawString("Engine Temp: ", 20, 30);
      tft.drawString(String(temp_hum_val[1]), 180, 145);
      delay(1000);
    } else {
      tft.fillScreen(TFT_RED);
      tft.setTextColor(TFT_WHITE);
      tft.setTextSize(3);
      tft.setCursor(50, 50);
      tft.drawString("Engine Temp: ", 20, 30);
      tft.drawString(String(temp_hum_val[1]), 180, 145);
      delay(1000);
    }
  }
}


//This is used to measure the distance between your car and the car behind. An alert will be issued on the LCD if its too close
void readUltrasonic() {

  Ultrasonic ultrasonic(4);
  long RangeInInches;
  long RangeInCentimeters;
  ultrasonic.MeasureInCentimeters();
  delay(200);
  Serial.print("Distance in cms: ");
  Serial.println(ultrasonic.RangeInCentimeters);

  if (ultrasonic.RangeInCentimeters >= 5 && ultrasonic.RangeInCentimeters <= 14) {
    tft.fillScreen(TFT_RED);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(3);
    tft.setCursor(50, 50);
    tft.drawString("ALERT!", 20, 30);
  } 
  else if (ultrasonic.RangeInCentimeters >= 15 && ultrasonic.RangeInCentimeters <= 30) {
    tft.fillScreen(TFT_YELLOW);
    tft.setTextColor(TFT_RED);
    tft.setTextSize(3);
    tft.setCursor(50, 50);
    tft.drawString("CAR BEHIND", 20, 30);
  
  }else 
  {
    tft.fillScreen(TFT_WHITE);
    
  }
  // delay(2000);
}
