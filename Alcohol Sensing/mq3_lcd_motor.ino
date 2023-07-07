// #include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Pin definitions for LCD
#define PIN_RST  16
#define PIN_CE   17
#define PIN_DC   18
#define PIN_DIN  19
#define PIN_CLK  20
#define PIN_BL   21

// Create an instance of the Adafruit PCD8544 library for LCD
Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_CLK, PIN_DIN, PIN_DC, PIN_CE, PIN_RST);

// Motor Driver Pins
const int ena = 2;   // Enable pin for Motor A
const int in1 = 4;   // Input 1 pin for Motor A
const int in2 = 3;   // Input 2 pin for Motor A
const int in3 = 6;   // Input 1 pin for Motor B
const int in4 = 7;   // Input 2 pin for Motor B
const int enb = 5;   // Enable pin for Motor B

const int enc = 10;   // Enable pin for Motor A
const int in5 = 9;   // Input 1 pin for Motor A
const int in6 = 8;   // Input 2 pin for Motor A
const int in7 = 12;   // Input 1 pin for Motor B
const int in8 = 13;   // Input 2 pin for Motor B
const int endd = 11;   // Enable pin for Motor B

// Sensor Pins
const int analogSensor = A0;

// Motor Control Variables
const int motorSpeed = 200;  // Motor speed (0-255)
const int alcoholThreshold = 500;  // Analog threshold for alcohol detection

void setup() {
  // Set the motor control pins as outputs
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(enc, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
  pinMode(endd, OUTPUT);

  // Initialize the display
  display.begin();
  display.setContrast(50);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Alcohol:");
  display.display();

  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(analogSensor);

  // Display the readings on the LCD
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Alcohol:");
  display.setCursor(0, 10);
  display.print("Analog value = ");
  display.print(analogValue);
  display.display();

  Serial.print("Alcohol: ");
  Serial.print("Analog value = ");
  Serial.println(analogValue);

  if (analogValue > alcoholThreshold) {
    Serial.println("YES");

    // Stop all motors
    motorStop();
    delay(2000);
  } else {
    Serial.println("NO");

    // Run all motors in one direction at full speed
    motorForward();
    delay(2000);
  }
}

void motorForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ena, motorSpeed);
  analogWrite(enb, motorSpeed);
  digitalWrite(in6, HIGH);
  digitalWrite(in5, LOW);
  digitalWrite(in8, HIGH);
  digitalWrite(in7, LOW);
  analogWrite(enc, motorSpeed);
  analogWrite(endd, motorSpeed);
}



void motorStop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(ena, 0);
  analogWrite(enb, 0);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
  analogWrite(enc, 0);
  analogWrite(endd, 0);
}