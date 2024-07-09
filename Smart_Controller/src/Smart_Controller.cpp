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


// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

const int trigPin = D16;  
const int echoPin = D9;
const int TRIGPIN=D3;
const int ECHOPIN=D2;
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

void setup() {
pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  
	Serial.begin(9600);
  pinMode(TRIGPIN, OUTPUT);  
	pinMode(ECHOPIN, INPUT);  
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
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);

   digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance2: ");
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
}