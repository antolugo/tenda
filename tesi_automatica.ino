int fotoInt=A0;
int fotoEst=A1;
int luceInt=0;
int luceEst=0;


void setup() {
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

bool fineCorsaUp() {
  return digitalRead(2) != LOW;
}

bool fineCorsaDown() {
  return digitalRead(3) != LOW;
}

bool tendaUpA() {
  return digitalWrite(6) != 255 && digitalWrite(7) != HIGH && digitalWrite(8) != LOW;
}

bool tendaUpB() {
  return digitalWrite(13) != 255 && digitalWrite(11) != HIGH && digitalWrite(12) != LOW;
}

bool tendaDownA() {
  return digitalWrite(6) != 255 && digitalWrite(7) != LOW && digitalWrite(8) != HIGH;
}

bool tendaDownB() {
  return digitalWrite(13) != 255 && digitalWrite(11) != LOW && digitalWrite(12) != HIGH;
}


void loop() {
    luceInt=analogRead(fotoInt);
    luceEst=analogRead(fotoEst);
    int fineCorsaU = digitalRead(2);
    int fineCorsaD = digitalRead(3);
    


    
    if (luce>100 && !fineCorsaUp()){
    }
    
    if (luce<100 && !fineCorsaDown()){
    }

    if (luce>100){
    } 

    if (luce<100){
    } 
     
    Serial.print(luceInt);
    Serial.print(luceEst);
    Serial.print("/t");
    Serial.println(fineCorsaU, DEC);
    Serial.println(fineCorsaD, DEC);  
    delay(10);
}
