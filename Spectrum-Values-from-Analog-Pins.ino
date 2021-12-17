#include "MatesController.h"

MatesController mates = MatesController(Serial);

#define ANALOG_UPPER_LIMIT  1023 // Uno 10-bit upper limit

const int analogPins[] = {
  A0, A1, A2, A3, A4, A5
};

int errLedStatus = LOW;
void ErrorLed_Toggle() {
  errLedStatus = ~errLedStatus;
  digitalWrite(LED_BUILTIN, errLedStatus);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, errLedStatus);

  if (!mates.begin()) {
    // Display didn't send ready signal in time
    while (1) {
      ErrorLed_Toggle();
      delay(100);
    }
  }
}

void loop() {

  int pinValue;
  int16_t barValue;

  static uint8_t col = 0;
    
  pinValue = analogRead(analogPins[col]);
  barValue = map(pinValue, 0, ANALOG_UPPER_LIMIT, 0, 100);  
  mates.setMediaSpectrumValue(0, col, barValue);

  col++;
  if (col == 6) col = 0;  

}
