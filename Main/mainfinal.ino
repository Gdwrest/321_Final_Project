#include <Arduino.h>
#include <Servo.h>
#include <math.h>


Servo horizontal;
Servo vertical;

//pins
const int button_pin = 12;
const int trigHorizontal = 8;
const int echoHorizontal = 9;
const int trigVertical = 6;
const int echoVertical = 7;
int cmInt = 0;
float lastHorizontalCm = 0.0;
float lastVerticalCm = 0.0;
int lastButtonState = HIGH;
int currentButtonState = HIGH;
unsigned long lastDebounceTime = 0;
void buttonHandler();
void horizontalServo();
void verticalServo();

void setup() {
    Serial.begin(9600);

   
    pinMode(trigHorizontal, OUTPUT);
    pinMode(echoHorizontal, INPUT);

    pinMode(trigVertical, OUTPUT);
    pinMode(echoVertical, INPUT);

    delay(800);

    horizontal.attach(10);
    vertical.attach(11);

    horizontal.write(0);
    vertical.write(90);

    // Button
    pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
    buttonHandler();
}
void buttonHandler() {
    int reading = digitalRead(button_pin);

    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > 40) {
        if (reading != currentButtonState) {
            currentButtonState = reading;
        }
        if (currentButtonState == LOW) {
            Serial.println("Button Pressed\n");

            horizontalServo();
            verticalServo();

            Serial.print("Horizontal Distance: ");
            Serial.print(lastHorizontalCm, 1);
            Serial.println(" cm");
            Serial.print("Vertical Distance: ");
            Serial.print(lastVerticalCm, 1);
            Serial.println(" cm");

            
        }
    }

    lastButtonState = reading;
}

void verticalServo() {
    digitalWrite(trigVertical, LOW);
    delayMicroseconds(2);
    digitalWrite(trigVertical, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigVertical, LOW);

    unsigned long dur = pulseIn(echoVertical, HIGH, 30000UL);

    if (dur == 0) {
        Serial.println("Vertical Distance: out of range");
        return;
    }

    float cm = (dur * 0.0343f) / 2.0f;
    lastVerticalCm = cm;
    if (cm > 35.0f && cm < 40.0f)
        vertical.write(99);
    else if (cm > 40.0f && cm < 45.0f)
        vertical.write(96);
    else if (cm > 45.0f && cm < 50.0f)
        vertical.write(93);
    else if (cm > 50.0f && cm < 55.0f)
        vertical.write(90);

    delay(300);
}

void horizontalServo() {
    digitalWrite(trigHorizontal, LOW);
    delayMicroseconds(2);
    digitalWrite(trigHorizontal, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigHorizontal, LOW);

    unsigned long dur = pulseIn(echoHorizontal, HIGH, 30000UL);

    if (dur == 0) {
        Serial.println("Horizontal Distance: out of range");
        return;
    }

    float cm = (dur * 0.0343f) / 2.0f;
    lastHorizontalCm = cm;

    if (cm < 50.0f) {
        horizontal.write(20);
    }
    else if (cm > 100.0f) {
        horizontal.write(0);
    }
    else if (cm > 50.0f && cm < 100.0f) {
        cmInt = (int)cm - 50;
        cmInt = cmInt / 2;
        cmInt = 25 - cmInt;

        if (cmInt <= 0)
            horizontal.write(0);
        else
            horizontal.write(cmInt / 2);
    }

   delay(300);
}
