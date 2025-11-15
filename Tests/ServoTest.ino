#include <Servo.h>

Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(9600);
  servo1.attach(9);  
  servo2.attach(10);  
  Serial.println("Servo test starting...");
}

void loop() {
  // sweep both servos 0° → 180° → 0°
  for (int pos = 0; pos <= 180; pos += 10) {
    servo1.write(pos);
    servo2.write(180 - pos);
    Serial.print("Position: ");
    Serial.println(pos);
    delay(300);
  }

  for (int pos = 180; pos >= 0; pos -= 10) {
    servo1.write(pos);
    servo2.write(180 - pos);
    Serial.print("Position: ");
    Serial.println(pos);
    delay(300);
  }
}
