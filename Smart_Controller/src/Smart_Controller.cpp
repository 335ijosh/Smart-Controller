/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "Adafruit_BME280.h"
#include "Adafruit_SSD1306.h"
#include "Colors.h"
#include "Encoder.h"
#include "IoTClassroom_CNM.h"


// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(MANUAL);

const int trigPin = D16;  
const int echoPin = D9;
float duration, distance;

Adafruit_BME280 bme;
const int OLED_RESET=-1;
Adafruit_SSD1306 display(OLED_RESET);
int currentTime;
int lastSec;
int status;
int lastSecond;
int i;
int position;
const int brightness=255;

Encoder myEnc(D17,D15);
int inputValue;
int LEDSwitch;
const int Switch=D6;
const int REDLED=D4;
const int GREENLED=D5;
const int BLUELED=D7;


const int BULB=2; 
int perviousPosition;
int pp;
int color;
bool on,off;
const int ENCODERPIN=D6;
Button greybutton(ENCODERPIN);

const int MYWEMO=1;
const int MYWEMO1=2;
int BUTTON_PIN=D10;
bool buttonstate;
Button whitebutton(BUTTON_PIN);

int mode;

void setup() {
    Serial.begin(9600); 
  waitFor(Serial.isConnected,15000);
    WiFi.on();
  WiFi.clearCredentials();
  WiFi.setCredentials("IoTNetwork");
  
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }
  Serial.printf("\n\n");

pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);
	Serial.begin(9600);

  bme.begin(0x76); 
 Serial.begin (9600);
 waitFor (Serial .isConnected ,10000);
 Serial.println ("ready to go");
if (status == false) {
Serial.printf("BME280 at address 0x%02X failed to start", 0x76); 
}
 waitFor(Serial.isConnected,10000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);


}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
 digitalWrite(trigPin, LOW);
  delay(5000);
  digitalWrite(trigPin, HIGH);
  delay(5000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);


  currentTime = millis();
if((currentTime-lastSec)>2000){ 
  lastSec = millis();
 float tempC = bme.readTemperature();
 float tempF= 1.8*tempC+32;
float pressPA = bme.readPressure();
float inHg= 1/3386.0*pressPA+5;
float humidRH = bme.readHumidity();
 Serial.printf("Temperature%0.2f\n,Pressure%0.2f\n,Humidity%0.2f\n" ,tempF,pressPA,humidRH );
 display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.printf("Temperature%0.2f\n,Pressure%0.2f\n,Humidity%0.2f\n" ,tempF,pressPA,humidRH );
  display.display();
  display.clearDisplay();
}

 position = myEnc.read();
     if (position!=perviousPosition)
{
              pp=2.6*position;
              Serial.printf("i = %d,\n",position);
     perviousPosition= position;
     setHue(BULB,true,HueRainbow[color%7],pp,255);
}
  if (position >brightness)
{
   position =brightness;
   myEnc.write(brightness);
         Serial.printf("i = %d,\n",position);
}
if (position <0)
{
   position=0;
   myEnc.write(0);
        Serial.printf("i = %d,\n",position);
}
 if (LEDSwitch==true)
  {
    digitalWrite(GREENLED,LOW);
  }
else {
digitalWrite(REDLED,LOW);
}
   analogWrite(Switch,inputValue);
position =myEnc.read();
 inputValue = digitalRead(D3);
  Serial.printf("button state = %i,\n",inputValue);

      if(greybutton.isClicked()){
   on =!on;
 Serial.printf("Setting color of bulb %i to color %06i\n",BULB,HueRainbow[color%7]);
  setHue(BULB,true,HueRainbow[color%7],pp,255);
  color++;
   if (on)
  {
setHue(BULB,true,HueRainbow[color%7],pp,255);
  color++;
  }
    else
  {
setHue(BULB,false,HueRainbow[color%7],pp,255);
  }
    }
    
 if(whitebutton.isClicked()){
   on =!on;
        if (  mode>3)
        {
            mode=0;
        }
      mode++;
        if((mode==0)){
          wemoWrite(MYWEMO,HIGH);
          wemoWrite(MYWEMO1,LOW);
        }
         if((mode==1)){
          wemoWrite(MYWEMO,HIGH);
          wemoWrite(MYWEMO1,HIGH);
        }
         if((mode==2)){
          wemoWrite(MYWEMO,LOW);
          wemoWrite(MYWEMO1,HIGH);
        }
         if((mode==3)){
          wemoWrite(MYWEMO,LOW);
          wemoWrite(MYWEMO1,LOW);
         }
     Serial.printf("mode %i\n",mode);
     Serial.printf("Turning on Wemo# %i\n",MYWEMO);

  }
  else
  {
    wemoWrite(MYWEMO,LOW);
  }
}