This project is a servo-controlled car side-mirror adjustment system. The goal is to automatically reposition a side mirror based on distance data from ultrasonic sensors. When the driver presses a button, the system reads the sensor values, calculates how far the seat/mirror needs to move, and adjusts two servos to tilt the mirror horizontally and vertically.

Features
    •    Two-axis mirror movement (left/right + up/down)
    •    Ultrasonic distance measurement
    •    Push-button activation
    •    Debounced input handling
    •    Arduino Uno–based control
    •    Modular code structure for testing servos, sensors, and main logic separately

Hardware Used
    •    Arduino Uno
    •    Two SG90/MG90S servos
    •    HC-SR04 ultrasonic sensor
    •    Breadboard + jumper wires
    •    5V power from Arduino
    •    Optional: external 5V supply for smoother servo movement
