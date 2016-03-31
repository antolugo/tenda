/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 *
 * This example shows how to use ESP8266 Shield via Hardware Serial
 * (on Mega, Leonardo, Micro...) to connect your project to Blynk.
 *
 * Note: Ensure a stable serial connection to ESP8266!
 *       Firmware version 1.0.0 (AT v0.22) or later is needed.
 *       You can change ESP baud rate. Connect to AT console and call:
 *           AT+UART_DEF=115200,8,1,0,0
 *
 * Change WiFi ssid, pass, and Blynk auth token to run :)
 * Feel free to apply it to any other example. It's simple!
 *
 **************************************************************/
//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_HardSer.h>
#include <BlynkSimpleShieldEsp8266_HardSer.h>

// Set ESP8266 Serial object
#define EspSerial Serial

#define MARGIN 5

ESP8266 wifi(EspSerial);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "3b8dfe66343d4a02a41809810fac010d";

int fotoInt=A0;
int fotoEst=A1;
int luceInt=0;
int luceEst=0;
int luceTarget=0;
bool started=false;

void setup() {
  // Set console baud rate
  Serial.begin(9600);
  delay(10);
  // Set ESP8266 baud rate
  EspSerial.begin(115200);
  delay(10);
  Blynk.begin(auth, wifi, "TP-LINK_2.4GHz_8653F3", "18031986");
  
  pinMode(fotoEst, INPUT);
  pinMode(fotoInt, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT);
  Serial.begin(9600);
}

BLYNK_WRITE(V3) {
  BLYNK_LOG("Received new V3: %s", param.asStr());
  started=true;
  luceTarget=param.asInt();
}

bool fineCorsaUp() {
  return digitalRead(2) != LOW;
}

bool fineCorsaDown() {
  return digitalRead(3) != LOW;
}

bool tendaUpA(int s) {
   digitalWrite(6,s); 
   digitalWrite(7,HIGH); 
   digitalWrite(8,LOW);
}

bool tendaUpB(int s) {
   digitalWrite(13,s); 
   digitalWrite(11,HIGH); 
   digitalWrite(12,LOW);
}

bool tendaDownA(int s) {
   digitalWrite(6,s); 
   digitalWrite(7,LOW); 
   digitalWrite(8,HIGH);
}

bool tendaDownB(int s) {
   digitalWrite(13,s); 
   digitalWrite(11,LOW); 
   digitalWrite(12,HIGH);
}

void loop() {
  Blynk.run();
  logic();
}

bool directionUp(int luce, int target) {
    return luce < target;
}

bool moving(int luce, int target) {
    return abs(luce - target) > MARGIN;
}

bool speed(int luce, int target) {
    return luce - target;
}

void logic() {
  luceInt=analogRead(fotoInt);
  luceEst=analogRead(fotoEst);
  int fineCorsaU = digitalRead(2);
  int fineCorsaD = digitalRead(3);
  
  if (started && moving(luceInt, luceTarget)) {
   if (directionUp(luceInt, luceTarget)){
      tendaUpA(speed(luceInt, luceTarget));
      tendaUpB(speed(luceInt, luceTarget));
    } else {
      tendaDownA(speed(luceInt, luceTarget));
      tendaDownB(speed(luceInt, luceTarget));
    }
  }
   
  Serial.print(luceInt);
  Serial.print(luceEst);
  Serial.print("/t");
  Serial.println(fineCorsaU, DEC);
  Serial.println(fineCorsaD, DEC);  
  delay(10);
}
