#include <Arduino.h>
#include <GlobalDefines.h>
#include <M5Core2.h>

void setup() {

  M5.begin();
  pinMode(PORT_C, INPUT);  // Sets the specified pin to input mode.

}

void loop() {
  // put your main code here, to run repeatedly:
  M5.update();
}