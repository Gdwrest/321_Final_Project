void setup() {
  //Sensor basic test
  Serial.begin(9600);
  pinMode(9, OUTPUT);  
  pinMode(10, INPUT);   
  delay(800);
  Serial.println("=== Ultrasonic Sensor Test ===");
}

void loop() {

  digitalWrite(9, LOW);  delayMicroseconds(2);
  digitalWrite(9, HIGH); delayMicroseconds(10);
  digitalWrite(9, LOW);


  unsigned long dur = pulseIn(10, HIGH, 30000UL);
  if (dur == 0) {
    Serial.println("Distance: out of range");
  } else {
    float cm = (dur * 0.0343f) / 2.0f;
    Serial.print("Distance: "); Serial.print(cm, 1); Serial.println(" cm");
  }
  delay(300);
}
