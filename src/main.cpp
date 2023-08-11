#include <Arduino.h>
#include <GlobalDefines.h>
#include <M5Core2.h>

void setup() {

  M5.begin();
  pinMode(PORT_C, INPUT);  // Sets the specified pin to input mode.

  M5.Axp.SetLcdVoltage(2600);
  M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
  M5.Lcd.drawString("Humidity", 0, 0, 4);

}

void loop() {

  M5.update();

  delay(1000);

}