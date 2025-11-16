#include <Servo.h>
Servo horizontal;
Servo vertical;

const int button_pin=12;
int cmInt=0;
int eyeHeight=0;
int eyeDistance=0;
int hyp=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, INPUT);   
  delay(800);
  horizontial.attach(10);
  vertical.attatch(13);
  horizontal.write(0);
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
      horizontalServo();
      verticalServo();
    }
  }
  lastButtonState = reading;
}

void verticalServo(){
  digitalWrite(8, LOW);  delayMicroseconds(2);
  digitalWrite(8, HIGH); delayMicroseconds(10);
  digitalWrite(8, LOW);
  unsigned long dur = pulseIn(9, HIGH, 30000UL);
  if (dur == 0) {
    Serial.println("Vertical Distance: out of range");
  } else {
    float cm = (dur * 0.0343f) / 2.0f;
    if(cm > 50.0f && cm < 100.0f){
      eyeHeight=(int)cm;
      eyeHeight=eyeHeight - 10; //subtract height-average distance between top of head and eyes=eye height
      eyeDistance=cmInt;
      hyp=(eyeHeight*eyeHeight)+(eyeDistance*eyeDistance);
      double hypComplete=sqrt(hyp);
      double angle=asin(hypComplete);
      int servoAngle = angle*(180.0/PI);
      if(eyeHeight < 0){
        vertical.write(40);
      } else{
        vertical.write(static_cast<int>(round(servoAngle)));
      }
    }
    Serial.print("Distance: "); Serial.print(cm, 1); Serial.println(" cm"); Serial.print("\n V Servo Moved to: "); Serial.print(cmInt, 1); Serial.print("cm");
  }
  delay(300);
}

void horizontalServo(){
  digitalWrite(8, LOW);  delayMicroseconds(2);
  digitalWrite(8, HIGH); delayMicroseconds(10);
  digitalWrite(8, LOW);
  unsigned long dur = pulseIn(9, HIGH, 30000UL);
  if (dur == 0) {
    Serial.println("Horizontal Distance: out of range");
  } else {
    float cm = (dur * 0.0343f) / 2.0f;
    if(cm > 50.0f && cm < 100.0f){
      cmInt=(int)cm;
      cmInt=cmInt - 50;
      if(cmInt < 0){
        horizontal.write(0);
      } else{
        horizontal.write(cmInt);
      }
    }
    Serial.print("Distance: "); Serial.print(cm, 1); Serial.println(" cm"); Serial.print("\n H Servo Moved to: "); Serial.print(cmInt, 1); Serial.print("cm");
  }
  delay(300);
}


void loop() {
  // put your main code here, to run repeatedly:
  buttonHandler();
}
