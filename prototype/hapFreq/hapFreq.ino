
#define RESISTOR 10000 // Same value of the resistor used in circuit
#define RUBBERCORD A0 // Pin RUBBERCORD is connected to
#define DLED 13 // Pin DLED is connected to

const int threshold = 890;  // Arbitrary threshold level that's in the range of the analog input (0-1023)
const int hapticMotor = 3; // Connects hapticMotor to pin 3
const int headPhone = 9; // Connects headPhone output to pin 9

void setup() { 
  pinMode(DLED, OUTPUT); // Set DLED as output device
  pinMode(hapticMotor, OUTPUT); // Set headPhone as output device
  pinMode(headPhone, OUTPUT); // Set headPhone as output device
  Serial.begin(9600); // Baud rate - Speed at which the data is sent
}
   
void loop() { 
  int analogValue = analogRead(RUBBERCORD); // read the value of the potentiometer:

  if (analogValue > threshold) { // if the analog value is greater then the threshold, turn on the LED and play sound:
    noTone(headPhone); // Stop sound
    digitalWrite(DLED, HIGH); // Turn on LED
  
    int i=0;
      do {
        i++;
        digitalWrite(hapticMotor, HIGH); // Vibrate
        delay(200);  // delay 0.2 second
        digitalWrite(hapticMotor, LOW); // Stop vibrating
        delay(200); //delay 0.2 second
        }
        while(i<2); // Vibrate twice in a 2 second interval
      } 
      else {
        tone(headPhone, 500); // Send 1KHz sound signal...
        digitalWrite(DLED, LOW); // Turn off LED
      }

      int value; 
      int raw = 0; // Raw input value 
      int vin = 5; // Stores input voltage of 5V 
      float vout = 0; // Stores output voltage 
      float refresistor1 = 10; // Variable to store the R1 value 
      float refresistor2 = 0; //  Value is determined by the voltage that falls across after it has been measured
      float buffer = 0; // Buffer variable for calculation
      
      value = analogRead(RUBBERCORD); // Read the analog arbitrary value
      vout = (5.0 / 1023.0) * value; // Calculates the voltage 
      buffer = (vin / vout) - 1; 
      refresistor2 = refresistor1 / buffer;
      
      Serial.print("Analog reading ");  
      Serial.println(value); //Print analog value
//    Serial.print("Voltage: "); 
//    Serial.println(vout); //Print voltage value
//    Serial.print("Resistance: ");  
//    Serial.println(refresistor2); //Print risistance value  
//    delay(1000); 
}
