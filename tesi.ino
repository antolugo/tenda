int fotor=A0;
int luce=0;

void setup() {
 pinMode(fotor, INPUT);
 pinMode(7, OUTPUT);
 pinMode(8, OUTPUT);
 pinMode(9, OUTPUT);
 pinMode(13, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(11, OUTPUT);
}

void loop() {
    luce=analogRead(fotor);
    int sensorValue = digitalRead(2);

    
    if (luce>100 && digitalRead(2) == LOW){
      digitalWrite(8, HIGH);
      digitalWrite(7, LOW);
      analogWrite(9, 255);

      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      analogWrite(11, 255);
      delay(10);
    }
    
    if (luce<100){
      digitalWrite(8, LOW);
      digitalWrite(7, HIGH);
      analogWrite(9, 255);

      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      analogWrite(11, 255);
      delay(10);
    }

    if (luce>100 && digitalRead(2) == HIGH){
      digitalWrite(8, LOW);
      digitalWrite(7, LOW);
      analogWrite(9, 255);

      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      analogWrite(11, 255);
      delay(10);
     } 
    Serial.print(luce);
    Serial.print("/t");
    Serial.println(sensorValue, DEC);
    delay(10);
}