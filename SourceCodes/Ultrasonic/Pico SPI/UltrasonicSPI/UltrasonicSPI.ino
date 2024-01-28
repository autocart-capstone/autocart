/*
        Ultrasonic Sensors interaced with Pico, which sends data through SPI to KL25Z
*/
#include <stdlib.h>
#include <SPI.h>
#include <SPISlave.h>


//Ultrasonic Variables

//Left
const int triggerPinL = 0; 
const int echoPinL = 1;
const int ledPinL = 8;
volatile long startTimeL = 0;
volatile long endTimeL = 0;
volatile boolean pinHighL = false;

//Middle
const int triggerPinM = 2; 
const int echoPinM = 3;
const int ledPinM = 7;
volatile long startTimeM = 0;
volatile long endTimeM = 0;
volatile boolean pinHighM = false;

//Right
const int triggerPinR = 4; 
const int echoPinR = 5;
const int ledPinR = 6;
volatile long startTimeR = 0;
volatile long endTimeR = 0;
volatile boolean pinHighR = false;


//SPI SETUP
/*
MOSI: 19
MISO: 16
SCK: 18
SS: 17

GUIDE: 
https://arduino-pico.readthedocs.io/en/latest/spi.html
https://github.com/earlephilhower/arduino-pico/blob/master/libraries/SPISlave/examples/SPItoMyself/SPItoMyself.ino

*/


void setup() {
  //Left
  pinMode(triggerPinL, OUTPUT);  // Sensor Trigger Pin
  pinMode(echoPinL, INPUT);     // Sensor Echo Pin 
  attachInterrupt(digitalPinToInterrupt(echoPinL), echoReceivedL, CHANGE);  //Interrupt to be triggered on ANY edge of echo
  pinMode(ledPinL, OUTPUT);

  //Middle
  pinMode(triggerPinM, OUTPUT);  // Sensor Trigger Pin  
  pinMode(echoPinM, INPUT);     // Sensor Echo Pin 
  attachInterrupt(digitalPinToInterrupt(echoPinM), echoReceivedM, CHANGE);  //Interrupt to be triggered on ANY edge of echo
  pinMode(ledPinM, OUTPUT);

  //Right
  pinMode(triggerPinR, OUTPUT);  // Sensor Trigger Pin  
  pinMode(echoPinR, INPUT);     // Sensor Echo Pin 
  attachInterrupt(digitalPinToInterrupt(echoPinR), echoReceivedR, CHANGE);  //Interrupt to be triggered on ANY edge of echo
  pinMode(ledPinR, OUTPUT);

  //SPI SETUP
  SPISettings spisettings(1000000, MSBFIRST, SPI_MODE0);
  int msg[1];
  memset(msg, 0, sizeof(msg));

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
  long distancecmL = (pulseWidthL * 0.0343) /2;
  if ((0 < distancecmL) && (distancecmL < 60)) {
    digitalWrite(ledPinL, HIGH);
  }
  else {
    digitalWrite(ledPinL, LOW);
  }
  
  Serial.print("Left Sensor: ");
  Serial.println(distancecmL);

  //Middle
  long pulseWidthM = endTimeM - startTimeM;
  long distancecmM = (pulseWidthM * 0.0343) /2;
  if ((0 < distancecmM) && (distancecmM < 60)) {
    digitalWrite(ledPinM, HIGH);
  }
  else {
    digitalWrite(ledPinM, LOW);
  }
  
  Serial.print("Middle Sensor: ");
  Serial.println(distancecmM);

  //Right
  long pulseWidthR = endTimeR - startTimeR;
  long distancecmR = (pulseWidthR * 0.0343) /2;
  if ((0 < distancecmR) && (distancecmR < 60)) {
    digitalWrite(ledPinR, HIGH);
  }
  else {
    digitalWrite(ledPinR, LOW);
  }
  
  Serial.print("Right Sensor: ");
  Serial.println(distancecmR);

  //SPI SEND DATA
  if((distancecmL<5) || (distancecmM<5) || (distancecmR<5)){ //STOP
    msg[0] = 0; //0 signals Stop
    SPI.beginTransaction(spisettings);
    SPI.transfer(msg, sizeof(msg));
    SPI.endTransaction();
  } else{ //GO
    msg[0] = 1; //1 signals Go
    SPI.beginTransaction(spisettings);
    SPI.transfer(msg, sizeof(msg));
    SPI.endTransaction();
  }

}
