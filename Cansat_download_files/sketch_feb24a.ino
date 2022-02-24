#include "MQ7.h"
#include "CO2Sensor.h"

CO2Sensor co2Sensor(A0, 0.99, 100);

#define A_PIN 2
#define VOLTAGE 5

#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10\
#define buzzerPin 12 
Adafruit_BMP280 bmp;
const int BMP_address = 0x76;
SoftwareSerial mySerial(9,10);
int number = 0;



const unsigned long eventInterval = 100;
unsigned long previousTime = 0;

// init MQ7 device
MQ7 mq7(A_PIN, VOLTAGE);






void setup() {
  Serial.begin(9600);
  int buzzerPin = 12;

  pinMode(buzzerPin, OUTPUT);
  
  mySerial.begin(9600);
  while (!Serial) {
    ; // wait for serial connection
  }

  Serial.println("");   // blank new line

  Serial.println("Calibrating MQ7");
  mq7.calibrate();    // calculates R0
  Serial.println("Calibration done!");

  Serial.println(F("BMP280 test"));
  bmp.begin(BMP_address);
  
  
  Serial.println("=== Initialized ===");
 
    co2Sensor.calibrate();

  pinMode(buzzerPin, OUTPUT);
}
 
void loop() {
 mySerial.print("PPM = "); mySerial.println(mq7.readPpm());

  mySerial.println("");   // blank new line
delay(1000);

delay (1000);
mySerial.print(F("Temperature = "));
    mySerial.print(bmp.readTemperature());
    mySerial.println(" *C");
    
    mySerial.print(F("Pressure = "));
    mySerial.print(bmp.readPressure());
    mySerial.println(" Pa");

    mySerial.print(F("Approx altitude = "));
    mySerial.print(bmp.readAltitude(1007)); // this should be adjusted to your local forcase
    mySerial.println(" m");
    
    mySerial.println();
    delay(2000);

    int waarde = co2Sensor.read();
  mySerial.print("CO2 waarde:");
  mySerial.print(waarde);
  mySerial.println("ppm.");

  class Buzzer{
  public:
  int buzzerPin;
  unsigned long currentTime;
  const unsigned long eventInterval = 100;
  unsigned long previousTime = 0;

    void update(){
      if(bmp.readAltitude(1007) <= 10){
      unsigned long currentTime = millis();
    }

    if (currentTime - previousTime >= eventInterval){
  tone(buzzerPin, 4000 ,50);
  previousTime = currentTime;
  
  }
}
};


  

}
