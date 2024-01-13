/*
        A simple code to trigger and echo a SINGLE Ultrasonic Sensor
*/
#include <stdlib.h>

//Ultrasonic Variables

//Left
const int triggerPinL = 0; 
const int echoPinL = 1; 
volatile long startTimeL = 0;
volatile long endTimeL = 0;
volatile boolean pinHighL = false;

//Middle
const int triggerPinM = 2; 
const int echoPinM = 3; 
volatile long startTimeM = 0;
volatile long endTimeM = 0;
volatile boolean pinHighM = false;

//Right
const int triggerPinR = 4; 
const int echoPinR = 5; 
volatile long startTimeR = 0;
volatile long endTimeR = 0;
volatile boolean pinHighR = false;


void setup() {
  //Left
  pinMode(triggerPinL, OUTPUT);  // Sensor Trigger Pin  
  pinMode(echoPinL, INPUT);     // Sensor Echo Pin 
  attachInterrupt(digitalPinToInterrupt(echoPinL), echoReceivedL, CHANGE);  //Interrupt to be triggered on ANY edge of echo

  //Middle
  pinMode(triggerPinM, OUTPUT);  // Sensor Trigger Pin  
  pinMode(echoPinM, INPUT);     // Sensor Echo Pin 
  attachInterrupt(digitalPinToInterrupt(echoPinM), echoReceivedM, CHANGE);  //Interrupt to be triggered on ANY edge of echo

  //Right
  pinMode(triggerPinR, OUTPUT);  // Sensor Trigger Pin  
  pinMode(echoPinR, INPUT);     // Sensor Echo Pin 
  attachInterrupt(digitalPinToInterrupt(echoPinR), echoReceivedR, CHANGE);  //Interrupt to be triggered on ANY edge of echo

  Serial.begin(115200); 
}

//Ultrasonic Code
void echoReceivedL() {
  //Rising Edge
  if (digitalRead(echoPinL) == HIGH) {
    startTimeL = micros(); //Calculate start of Pulse Width
    pinHighL = true; //Pin is High

  //Falling Edge
  } else if (pinHighL) {
    endTimeL = micros(); //Calculate end of Pulse Width
    pinHighL = false; //Pin is Low
  }
}

void echoReceivedM() {
  //Rising Edge
  if (digitalRead(echoPinM) == HIGH) {
    startTimeM = micros(); //Calculate start of Pulse Width
    pinHighM = true; //Pin is High

  //Falling Edge
  } else if (pinHighM) {
    endTimeM = micros(); //Calculate end of Pulse Width
    pinHighM = false; //Pin is Low
  }
}

void echoReceivedR() {
  //Rising Edge
  if (digitalRead(echoPinR) == HIGH) {
    startTimeR = micros(); //Calculate start of Pulse Width
    pinHighR = true; //Pin is High

  //Falling Edge
  } else if (pinHighR) {
    endTimeR = micros(); //Calculate end of Pulse Width
    pinHighR = false; //Pin is Low
  }
}


void loop() {

  //Send Ultrasonic Trigger

  //Left
  digitalWrite(triggerPinL, HIGH);  
  delayMicroseconds(10);
  digitalWrite(triggerPinL, LOW);

  //Middle
  digitalWrite(triggerPinM, HIGH);  
  delayMicroseconds(10);
  digitalWrite(triggerPinM, LOW);

  //Right
  digitalWrite(triggerPinR, HIGH);  
  delayMicroseconds(10);
  digitalWrite(triggerPinR, LOW);

  delay(30);

  //Calculate Pulse Width of Ultrasonic Sensor Echo

  //Left
  long pulseWidthL = endTimeL - startTimeL;
  Serial.print("Left Sensor: ");
  Serial.println(pulseWidthL);

  //Middle
  long pulseWidthM = endTimeM - startTimeM;
  Serial.print("Middle Sensor: ");
  Serial.println(pulseWidthM);

  //Right
  long pulseWidthR = endTimeR - startTimeR;
  Serial.print("Right Sensor: ");
  Serial.println(pulseWidthR);

}
