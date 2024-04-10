
#include "record_sound.h"
#include <cstdint>
#include <cstddef>
#include <algorithm>

const int buttonPin = 14; // For draw button
const int clearPin = 15; // For clear button
int buttonState1 = 0; // For draw button
int buttonState2 = 0; //For clear button

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Set up draw button as input
  pinMode(clearPin, INPUT_PULLUP); // Set up clear button as input

  Serial.begin(115200); // Changing this doesn't actually change the serial speed
  digitalWrite(LED_BUILTIN, 1);
  while (!Serial)
    ; // delay long enough for serial to get set up
  String str = Serial.readStringUntil('\n');
  str.trim();
  if (str != "freq") {
    Serial.println("did not get freq");
    while (true);
  }
  int fs = Serial.readStringUntil('\n').toInt();
  fs = std::clamp(fs, 8000, 50000);

  setup_sound_in(fs);
}

bool first = true;
size_t buffer_ind = 0;
byte buffer[64];

void loop()
{

  if (Serial.available() > 0)
  {
    String str = Serial.readStringUntil('\n');
    str.trim();
    if (str == "freq") {
      String _freq = Serial.readStringUntil('\n'); // skip freq reading
      return;
    }

    // For draw button
    buttonState1 = digitalRead(buttonPin);
    if (buttonState1 == LOW){
      Serial.println("press");
    }
    else{
      Serial.println("yyyyy");
    }

    //For clear button
    buttonState2 = digitalRead(clearPin);
    if (buttonState2 == LOW){
      Serial.println("cleared");
    }
    else{
      Serial.println("xxxxxxx");
    }
    int num_samples = str.toInt();
    for (int i = 0; i < num_samples; i++)
    {
      int16_t sample = get_sample();
      buffer[buffer_ind] = (sample >> 0) & 0xFF;
      buffer_ind++;
      buffer[buffer_ind] = (sample >> 8) & 0xFF;
      buffer_ind++;
      // buffer[buffer_ind] = (sample >> 16) & 0xFF;
      // buffer_ind++;
      // buffer[buffer_ind] = (sample >> 24) & 0xFF;
      // buffer_ind++;
      if (buffer_ind == 64)
      {
        Serial.write(buffer, 64);
        buffer_ind = 0;
      }
    }
    if (buffer_ind > 0)
    {
      Serial.write(buffer, buffer_ind);
      buffer_ind = 0;
    }
    Serial.flush();
  }
  else
  {
    int16_t discarded_sample = get_sample();
    (void)discarded_sample;
  }
}
