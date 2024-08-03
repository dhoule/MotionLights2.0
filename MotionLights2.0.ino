#include <Adafruit_DotStar.h>
#include <SPI.h> 

// Here's how to control the LEDs from any two pins:
#define NUMPIXELS  89
#define DATAPIN    2
#define CLOCKPIN   3
#define ELAPSED    30000 // time, in milliseconds, to leave LEDs on
#define NEEDED     70 // LDR value to be equal to, or lower than

Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN);

int sensorPin1 = A0;             // select the input pin for Photoresistor1
int inputPin1 = 4;               // choose the input pin (for PIR sensor 1)
int inputPin2 = 5;               // choose the input pin (for PIR sensor 2)
int pirState = LOW;             // we start, assuming no motion detected
int val1 = 0;                    // variable for reading the pin status of PIR sensor 1
int val2 = 0;                    // variable for reading the pin status of PIR sensor 2
int lightValue = 0;             // Store value from photoresistor (0-1023)
unsigned long startTime = 0;    // Used to determine when state changed from 0 to 1
int calibrationTime = 30;       // Let the sensors calibrate for a number of secs

void setup() {
  pinMode(inputPin1, INPUT);     // declare sensor as input
  pinMode(inputPin2, INPUT);     // declare sensor as input
  pinMode(sensorPin1, INPUT);     // declare Photoresistor as input
  digitalWrite(inputPin1, LOW);   // Force the pin to be LOW
  digitalWrite(inputPin2, LOW);   // Force the pin to be LOW
  strip.begin(); // Initialize pins for output
  strip.clear();
  strip.show();  // Turn all LEDs off ASAP
  Serial.begin(9600);
}

void loop(){
  lightValue = analogRead(sensorPin1);
  // Determine if the area is dark enough to continue or not
  if(lightValue <= NEEDED){
    val1 = digitalRead(inputPin1);  // read input value of PIR sensor 1
    val2 = digitalRead(inputPin2);  // read input value of PIR sensor 2
    if (val1 == HIGH && val2 == HIGH) {            // check if the input is HIGH
      // turn lights on
      strip.fill(0xFF0000); // 'On' pixel one at a time
      strip.show();
      // Just wait the elapsed amount of required time
      delay(ELAPSED);
      digitalWrite(inputPin1, LOW);   // Force the pin to be LOW
      digitalWrite(inputPin2, LOW);   // Force the pin to be LOW
    }
  }
  // Just for CYA sake, turn the LED strip off no matter what
  strip.clear();
  strip.show();
  // just a slight rest 
  delay(500);
}
