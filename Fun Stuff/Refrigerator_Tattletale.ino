#include <Digital_Light_TSL2561.h>
#include <Wire.h>
#include <Adafruit_SleepyDog.h>


//need some constants for light sensor - you may have to adjust values to ones that work, even if the door is cracked opena bit

const uint32_t DARK_THRESHOLD =10;

const int BUZZER_PIN = WIO_BUZZER;
const int OPEN_WARNING_TONE = 500;
const int OPEN_WARNING_DURATION_MS = 1000;
const int TEMP_WARNING_TONE = 800;
const int TEMP_WARNING_DURATION_MS = 500;
const int TEMP_WARNING_REPEAT =3;


//constant for warning thresholds and repeat intervals 
const uint32_t OPEN_WARNING_TIME_SEC = 60;
const uint32_t OPEN_WARNING_INTERVAL_SEC = 16;

const int8_t TEMP_WARNING_LOW_CELSIUS = 20; //USE 1 IF IN FRIDGE
const int8_t TEMP_WARNING_HIGH_CELSIUS = 23;//USE 4 IF IN FRIDGE
const uint32_t TEMP_WARNING_INTERVAL_SEC = 5;

//the timers are turned off during sleep()
// need var to keep track of time using Watchdog timer (i.e., Sleepydog)

uint32_t nLoopStart = 0;
uint32_t nApproxRunTime = 0;

//variables to keep track of our warnings
bool bLightOn = false; 
uint32_t nLightOnStart = 0; 
uint32_t nLastLightOnWarning =0;

bool bTempProblem = false; 
uint32_t nLastTempOnWarning =0;

//temp sensor stuff
#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN 0
DHT dht(DHTPIN,DHTTYPE);
int nTemp=0;
//led

const int LED_PIN = LED_BUILTIN;

//vib motor
const int VIBRATION_PIN = 4; 

//LCD
#include <TFT_eSPI.h>
TFT_eSPI tft; 
TFT_eSprite spr = TFT_eSprite(&tft);

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  TSL2561.init();

  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,LOW);

  pinMode(VIBRATION_PIN,OUTPUT);
  digitalWrite(VIBRATION_PIN,LOW);

  //lcd
  tft.begin();
  tft.setRotation(3);
  digitalWrite(LCD_BACKLIGHT, HIGH);
  tft.fillScreen(TFT_GREEN);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("Done setting up",10,10);
  delay(5000);

}

void loop() {
  //for testing only 
  digitalWrite(LCD_BACKLIGHT, HIGH);
  tft.fillScreen(TFT_YELLOW);
  tft.setTextColor(TFT_BLACK);
  tft.drawString("looping",10,0);
  delay(250);

  //to keep track of time, we set nLoopStart at the top of the loop 
  //adjust nApproxRunTime for sleep time at the bottom of the loop
  //not super precise

  nLoopStart = millis();
   if(lightCheck() == "LIGHT"){//light is on
   //if wasnt light last time through loop

    if(!bLightOn){
      //set light flag reset our light on duration
      bLightOn = true;
      nLightOnStart = approxRunTime();
    }else{
      //if it was light before and light longer than our threshold..

      if ((approxRunTime() -nLightOnStart)>= (OPEN_WARNING_TIME_SEC *1000)){
        //and if last light warning no longer than interval
        if((approxRunTime() - nLastLightOnWarning) >= (OPEN_WARNING_INTERVAL_SEC * 1000)){
          //reset warning time
          nLastLightOnWarning = approxRunTime();
          digitalWrite(LCD_BACKLIGHT, HIGH);
          tft.fillScreen(TFT_RED);
          tft.drawString("LIGHT WARNING", 10,20);
          tft.drawString("LIGHT CHECK",10,30);
          tft.drawString(lightCheck(),10,40);
          warningTone(OPEN_WARNING_TONE,OPEN_WARNING_DURATION_MS,1);
        }
      }
    }//esle for !bLIghtOn
   }//if light is on
    else{
      //make if light flag is off
      bLightOn = false; 
      // digitalWrite(LCD_BACKLIGHT,LOW);

    }//else

    //check temperature
  checkTemperature();
  //determine loop sleep time based on conditions
  int nSleepTime = 16000; //16 sec of std sleep time  = 2x mac watchdog timer

  //adjust loop sleep time based on whether it is light or not
  //save battery by sleeping longer during darknesss
  //if detected light > 60+ seconds, should hear a warning beep about every 16 sec

  if(bLightOn){
    nSleepTime = min(nSleepTime, (OPEN_WARNING_INTERVAL_SEC*1000));
  }
  // adjust sleep time when in a temp warning so warning will be close to desired intervals. 
  if (bTempProblem){
    nSleepTime = min(nSleepTime, (TEMP_WARNING_INTERVAL_SEC*1000));
  }
  //BEFORE SLEEPING, UPDATE APPORX RUN TIME
  updateApproxRunTimeForSleep(nSleepTime);

  //sleep in max of 8 sec intervals --> max time in the lib  up to a max of 16 sec
  while(nSleepTime>0){
    Watchdog.sleep(8000);
    nSleepTime -= 8000;
  }

  //sleep terminates USB connection.  - if need to reprogram, reset the wio
  delay(250);



}//loop

  uint32_t approxRunTime(){
    return(nApproxRunTime + (millis()-nLoopStart));

  }

  void updateApproxRunTimeForSleep(uint32_t nSleepTime){
    nApproxRunTime +=(millis()-nLoopStart) + nSleepTime;
    nLoopStart = millis();//reset loop start since we've added loop time to total
  }

  void checkTemperature(){
    tft.drawString("Check temp",10,20);

    //if temp is outta range
    if(!tempOkay()){
      bTempProblem = true;
      //check interval 
      if((approxRunTime() - nLastTempOnWarning) > (TEMP_WARNING_INTERVAL_SEC *1000)){
        //RESET WARNING TIME
        nLastTempOnWarning = approxRunTime();
        //give warnign
        digitalWrite(LCD_BACKLIGHT,HIGH);
        tft.fillScreen(TFT_BLUE);
        tft.drawString("TEMP Warning",10,40);
        tft.drawString("TEMP",10,65);
        tft.drawString(String(nTemp),10,85);

        warningTone(TEMP_WARNING_TONE,TEMP_WARNING_DURATION_MS,TEMP_WARNING_REPEAT);
      }
    }//IF TEMP OKAY
    else{
      bTempProblem = false;
      // digitalWrite(LCD_BACKLIGHT,LOW);
    }
  }//check temp 

  bool tempOkay(){
    tft.drawString("TEMP OK",10,200);
    bool bTempOkay = true;

    float temp_hum_val[2] = {0};
    if(!dht.readTempAndHumidity(temp_hum_val)){
      nTemp = temp_hum_val[1];
      tft.drawString("TEMP",10,65);
      tft.drawString(String(nTemp),10,85);
      delay(250);

    }
    //if temp not in range
    if((nTemp < TEMP_WARNING_LOW_CELSIUS) ||
        (nTemp > TEMP_WARNING_HIGH_CELSIUS)){
          bTempOkay = false;
        }
        return bTempOkay;

  }//tempOkay()


String lightCheck(){
  tft.drawString("Checking light",10,115);
  String strOut ="LIGHT";

  if(TSL2561.readVisibleLux() <= DARK_THRESHOLD){
    strOut ="DARK";
  }
  tft.drawString("LIGHT CHECK",10,135);
  tft.drawString(strOut,10,155);
  return strOut;
}


void warningTone(uint16_t nFreq, uint16_t nDuration, uint8_t nCount){

  int n=0;
  while(n++ <nCount){
    playTone(BUZZER_PIN, nFreq, nDuration); 
    flashLED(nDuration); //flash led and vibrate

    //if repeating pause briefly so tones dont run together 
    if(n< nCount){
      delay(250);
    }
  }
  
}

void playTone(uint8_t nPin, uint16_t nFreq, uint16_t nDuration){
 
    if (nFreq ==0 || nDuration ==0 ){
      noTone(nPin);
    }
    else{
      tone(nPin, nFreq, nDuration);
    }
    delay(nDuration); //for sync playing
}
  
void flashLED(uint16_t nDuration){
  tft.drawString("Flashing lED and vibrating",10,215);
  digitalWrite(VIBRATION_PIN, HIGH);
  digitalWrite(LED_PIN,HIGH);
  delay(nDuration);

  digitalWrite(VIBRATION_PIN, LOW);
  digitalWrite(LED_PIN,LOW);
  delay(nDuration);

  digitalWrite(VIBRATION_PIN, HIGH);
  digitalWrite(LED_PIN,HIGH);
  delay(nDuration);

  digitalWrite(VIBRATION_PIN, LOW);
  digitalWrite(LED_PIN,LOW);
  delay(nDuration);
}
 
