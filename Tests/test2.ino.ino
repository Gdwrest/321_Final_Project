#include <Servo.h>
Servo servo1;


void setup() {

  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);  
  servo1.attach(10);
  delay(800);
}


void loop() {
  digitalWrite(8, LOW);  delayMicroseconds(2);
  digitalWrite(8, HIGH); delayMicroseconds(10);
  digitalWrite(8, LOW);




  unsigned long dur = pulseIn(9, HIGH, 30000UL);
  if (dur == 0) {
    Serial.println("Distance: out of range");
  } else {
    float cm = (dur * 0.0343f) / 2.0f;
    if(cm > 100.0f){
      servo1.write(180);
      Serial.print("Moving Servo...");
    }
    Serial.print("Distance: "); Serial.print(cm, 1); Serial.println(" cm");
  }
  delay(300);
}
