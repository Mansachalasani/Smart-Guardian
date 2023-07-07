#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
const int buzzerPin = 2;       // Pin number for the buzzer

PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {   

  Serial.begin(9600);          // For Serial Monitor
  pinMode(buzzerPin, OUTPUT);  // Set buzzer pin as an output

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   

   
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}



void loop() {

 int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 

if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened". 
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM: " 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 

  if(myBPM<60){
  tone(buzzerPin, 1000);
  delay(1000);// Check if BPM is less than 60
} else {
  noTone(buzzerPin);
  
}
}

  delay(20);                    

}

//int buzzerPin = 2; // pin number connected to the buzzer
//
//void setup() {
//  pinMode(buzzerPin, OUTPUT); // declare the pin as an output pin
//}
//
//void loop() {
//  digitalWrite(buzzerPin, HIGH); // turn the buzzer on
//  tone(buzzerPin, 450);
//  delay(1000); // wait for 1 second
//  digitalWrite(buzzerPin, LOW); // turn the buzzer off
//  noTone(buzzerPin);
//  delay(1000); // wait for 1 second
//}
