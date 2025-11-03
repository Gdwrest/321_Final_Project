#include <Servo.h>
Servo servo1;
const int button_pin=12;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);  
  delay(800);
  servo1.attach(10);
  pinMode(button_pin, INPUT_PULLUP);
}


int lastButtonState = HIGH;
int currentButtonState = HIGH;
unsigned long lastDebounceTime = 0;


void buttonHandler(){
  int reading =digitalRead(button_pin);
  if(reading != lastButtonState){
    lastDebounceTime=millis();
  }
  if((millis()-lastDebounceTime) > 40){
    if(reading != currentButtonState){
      currentButtonState = reading;
    }
    if(currentButtonState == LOW){
      Serial.println("Button Pressed!");
      Serial.println("\n");
      moveServos();
    }
  }
  lastButtonState = reading;
}




void moveServos(){
  digitalWrite(8, LOW);  delayMicroseconds(2);
  digitalWrite(8, HIGH); delayMicroseconds(10);
  digitalWrite(8, LOW);
  unsigned long dur = pulseIn(9, HIGH, 30000UL);
  if (dur == 0) {
    Serial.println("Distance: out of range");
  } else {
    float cm = (dur * 0.0343f) / 2.0f;
    if(cm > 75.0f){
      servo1.write(180);
    }else{
      servo1.write(0);
    }
    Serial.print("Distance: "); Serial.print(cm, 1); Serial.println(" cm");
  }
  delay(300);
}




void loop() {
  // put your main code here, to run repeatedly:
  buttonHandler();
}
