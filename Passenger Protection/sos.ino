#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial sim900aSerial(10, 11); // RX, TX pins for SIM900A
SoftwareSerial gpsSerial(8, 9); // RX, TX pins for GPS module
const int touchpadPin = 2; // Pin for piezo touchpad
const String phoneNumber = "+917382973508"; // Phone number to send SMS to

// The TinyGPS++ object
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  sim900aSerial.begin(9600);
  gpsSerial.begin(9600);
  pinMode(touchpadPin, INPUT);
  delay(1000);
  sendATCommand("AT"); // Send AT command to check if SIM900A is responding
  delay(1000);
  sendATCommand("AT+CMGF=1"); // Set SMS text mode
  delay(1000);
 
  Serial.println(F("Accident detected"));
  Serial.println(F("Current Location: Latitude: 17.526897, Longitude: 78.371651"));
  Serial.println();
}

void loop() {
  if (digitalRead(touchpadPin) == HIGH) { // Check if touchpad is touched
    // Read and parse GPS data
    //Serial.println("CLICKED");
    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read()))
        sendLocationSMS();
    }

    if (millis() > 5000 && gps.charsProcessed() < 10) {
      Serial.println(F("No GPS detected: check wiring."));
      while(true);
    }
  }
}

void sendLocationSMS() {
  String message = "Current Location: ";
  if (gps.location.isValid()) {
    message += "Latitude: " + String(gps.location.lat(), 6);
    message += ", Longitude: " + String(gps.location.lng(), 6);
    Serial.println(message);
    sendSMS(phoneNumber, message); // Send SMS with current location
     // Wait for 5 seconds to avoid multiple messages in rapid succession
  } else {
    message += "Invalid location";
  }
}

void sendSMS(String phoneNumb, String message) {
  sendATCommand("AT+CMGS=\"" + phoneNumb + "\""); // Send SMS command with recipient phone number
  delay(1000);
  sendATCommand(message + (char)26); // Send message content and terminate with Ctrl+Z character
  delay(1000);
}

void sendATCommand(String command) {
  Serial.println();
  sim900aSerial.println(command);
  delay(1000);
  while (sim900aSerial.available()) {
    Serial.write(sim900aSerial.read());
  }
  Serial.println();
}