//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266_HardSer.h>
#include <BlynkSimpleShieldEsp8266_HardSer.h>

// Set ESP8266 Serial object
#define EspSerial Serial

#define MARGIN 15

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
  pinMode(fotoEst, INPUT);
  pinMode(fotoInt, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Blynk.begin(auth, wifi, "TP-LINK_2.4GHz_8653F3", "18031986");
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

void stopAll() {
  digitalWrite(13,0); 
  digitalWrite(6,0); 
}

void loop() {
  Blynk.run();
  lastMillis = millis()
  if (500 < (millis()-lastMillis)) {
    lastMillis = millis();
    logic();
  }
}

bool directionUp(int luce, int target) {
    return luce < target;
}

bool moving(int luce, int target) {
    return abs(luce - target) > MARGIN;
}

bool speed(int luce, int target) {
  int diff = abs(luce - target);
    if (diff < 255) {
      return diff;
    } else {
      return 255;
    }
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
  } else (stopAll()) {
    
  }

  BLYNK_LOG("Luce interna: %d",luceInt);
  BLYNK_LOG("Luce esterna: %d",luceEst);
  BLYNK_LOG("Fine corsa Up: %d",fineCorsaU);
  BLYNK_LOG("Fine corsa Down: %d",fineCorsaD);
  
  delay(1000);
}
