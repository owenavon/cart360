#include "pitches.h"

#define RESISTOR 10000 //This should be the same value of the used resistor  
#define RUBBERCORDPIN A0  //This is the pin where the cord is connected tp
#define DLED 13

const int threshold = 890;  // an arbitrary threshold level that's in the range of the analog input

const int motorPin = 3; //motor transistor is connected to pin 3
const int headPhones = 9; //buzzer to arduino pin 9
const int maxNotes = 2;

// notes array
int notes[]={NOTE_B0,NOTE_E1,NOTE_A1,NOTE_E5,NOTE_FS6,NOTE_GS7,NOTE_CS8,NOTE_B7,NOTE_CS7,NOTE_FS6};

// current note
int currentNote = 0;

void setup() { 
  pinMode(DLED, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(headPhones, OUTPUT); // Set buzzer - pin 9 as an output
  Serial.begin(9600);
}

void vibeSound() {
  int analogValue = analogRead(RUBBERCORDPIN); // read the value of the potentiometer:

  // Current chosen note is less then 9
  if (currentNote < maxNotes) {
    if (analogValue > threshold) { // if the analog value is greater then the threshold, turn on the LED and play sound:
      noTone(headPhones);
      currentNote++;
      digitalWrite(DLED, HIGH); // Ardunio LED

      // Vibration Motors
      int j=0;
      do {
        j++;
        digitalWrite(motorPin, HIGH); //vibrate
        delay(200);  // delay 0.2 second
        digitalWrite(motorPin, LOW);  //stop vibrating
        delay(200); //delay 0.2 second
      }
      while(j<2);
      delay (2000); // delay 2 seconds between vibrations
      }
       
      else {
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
    }

    int value; 
    int raw = 0; // Raw input value 
    int vin = 5; // Store input voltage, this should be 5 
    float vout = 0; // Store output voltage 
    float refresistor1 = 10; // Variable to store the R1 value 
    float refresistor2 = 0; //  Value is determined by the voltage that falls across after it has been measured
    float buffer = 0; // Buffer variable for calculation 
    value = analogRead(RUBBERCORDPIN); // Read the value that calculates the voltage
    vout = (5.0 / 1023.0) * value; // Displays 1023 as voltage
    buffer = (vin / vout) - 1; 
    refresistor2 = refresistor1 / buffer; 
    // Serial.print("Analog reading ");  
    // Serial.println(value); //Print value
    // Serial.print("Voltage: "); 
    // Serial.println(vout); // Outputs the information 
    // Serial.print("Resistance: ");  
    // Serial.println(refresistor2);   
    // delay(1000); 
}

void loop() { 
  vibeSound(); // Calls the vibeSound function
}
