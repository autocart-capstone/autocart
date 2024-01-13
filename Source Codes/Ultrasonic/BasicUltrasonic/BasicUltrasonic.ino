/*
        A simple code to trigger and echo a SINGLE Ultrasonic Sensor
*/
#include <stdlib.h>

const int triggerPin = 0; 
const int echoPin = 1; 
volatile long startTime = 0;
volatile long endTime = 0;
volatile boolean pinHigh = false;
volatile bool obstacleDetected = false;


void setup() {
  pinMode(triggerPin, OUTPUT);  // Sensor Trigger Pin  
  pinMode(echoPin, INPUT);     // Sensor Echo Pin 
  attachInterrupt(digitalPinToInterrupt(echoPin), echoReceived, CHANGE);  //Interrupt to be triggered on ANY edge of echo
  Serial.begin(115200); 
}

//Ultrasonic Code
void echoReceived() {
  //Rising Edge
  if (digitalRead(echoPin) == HIGH) {
    startTime = micros(); //Calculate start of Pulse Width
    pinHigh = true; //Pin is High

  //Falling Edge
  } else if (pinHigh) {
    endTime = micros(); //Calculate end of Pulse Width
    pinHigh = false; //Pin is Low
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //Send Ultrasonic Trigger
  digitalWrite(triggerPin, HIGH);  
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  delay(50);

  //Calculate Pulse Width of Ultrasonic Sensor Echo
  long pulseWidth = endTime - startTime;
  Serial.println(pulseWidth);

}
