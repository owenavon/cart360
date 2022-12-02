#include "pitches.h"

#define RESISTOR 10000 // Same value as resistor
#define RUBBER_CORD A0
#define DLED 13

const int threshold = 880;  // an arbitrary threshold level that's in the range of the analog input

const int motorPin = 3;
const int headPhones = 9; 
const int maxNotes = 10;

// notes array
int notes[10]={NOTE_B0,NOTE_E1,NOTE_A1,NOTE_E5,NOTE_FS6,NOTE_GS7,NOTE_CS8,NOTE_B7,NOTE_CS7,NOTE_FS6};

// current note
int currentNote = 0;

// Stretch Sensor
int ambiguousVal; 
int raw = 0; // Raw input value
int vin = 5; // Store input voltage - 5
float vout = 0; // Store output voltage 
float resistor = 10; // Variable to store the resistor value 
float buffer = 0; // Buffer variable for calculation

void(* resetFunc) (void) = 0; // Decleares reset function at address 0

void setup() { // Runs once, and sets pins to OUTPUT
  pinMode(DLED, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(headPhones, OUTPUT); 
  Serial.begin(9600);
}

void vibeSound() {
  int analogValue = analogRead(RUBBER_CORD); // read the value of the sensor (potentiometer)

  // Current chosen note is less then 9
  if (currentNote < maxNotes) {
    if (analogValue > threshold) { // Turn on the LED, motor vibrates, and pause audio output
      noTone(headPhones);
      currentNote++; // Increments through the array
      digitalWrite(DLED, HIGH); // Ardunio LED

      // Vibration Motors
      int i=0;
      do {
        i++;
        digitalWrite(motorPin, HIGH); //vibrate
        delay(200);  // delay 0.2 second
        digitalWrite(motorPin, LOW);  //stop vibrating
        delay(200); //delay 0.2 second
      }
      while(i<2);
      delay (1000); // delay 1 second between vibrations
      }
       
      else { // Play current note and turn off LED
        tone(headPhones, notes[currentNote]);
        digitalWrite(DLED, LOW);
      }
    }
    else {
      Serial.println("You've made it to the end of the sequence");

      // Blink LED 13
      digitalWrite(DLED, HIGH); // Ardunio LED
      delay(200);  // delay 0.2 second
      digitalWrite(DLED, LOW); // Ardunio LED
      delay(200);  // delay 0.2 second

      int j=0;
      do {
        j++;
        digitalWrite(motorPin, HIGH); //vibrate
        delay(100);  // delay 0.1 second
        digitalWrite(motorPin, LOW); // stop vibrating
        delay(100); //delay 0.1 second
      }
      while(j<10); // Vibrates sequence 10 times upon victory
      delay(2000); // Take 2 seconds to reset
      resetFunc();
    }
}

void stretchSensor() {
  ambiguousVal = analogRead(RUBBER_CORD); // Read the value that calculates the voltage
  vout = (5.0 / 1023.0) * ambiguousVal; // Displays 1023 as voltage
  buffer = (vin / vout) - 1;
    
  Serial.print("Analog reading ");  
  Serial.println(ambiguousVal); // Outputs the ambiguous (0-1024) value
     
  // Serial.print("Voltage: "); 
  // Serial.println(vout); // Outputs the volts
     
  // Serial.print("Resistance: ");  
  // Serial.println(resistor); // Outputs the ohms
       
  // delay(1000); 
}

void loop() { // Runs over and over
  vibeSound(); // Calls the vibeSound function
  stretchSensor(); // Calls the stretchSensor function
}
