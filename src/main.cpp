#include <Arduino.h>
#include <GlobalDefines.h>
#include <M5Core2.h>

const int DISP_OFFSET = 25;

void setup() {

  M5.begin();
  pinMode(PORT_C, INPUT);  // Sets the specified pin to input mode.

  M5.Axp.SetLcdVoltage(2600);
  M5.Lcd.setTextColor(TFT_GREEN, TFT_BLACK);
  M5.Lcd.drawString("Humidity", 0, 0, 4);

}

void loop() {

  M5.update();

  char buf[40];

  const float powerTemp = M5.Axp.GetTempInAXP192();
  sprintf(buf, "Powr Temp: %2.1fC", powerTemp);
  M5.Lcd.drawString(buf, 0, DISP_OFFSET, 4);

  const float batV = M5.Axp.GetBatVoltage();
  const float batA = M5.Axp.GetBatCurrent();
  sprintf(buf, "Batt.: %2.2fV %2.1fmA", batV, batA);
  M5.Lcd.drawString(buf, 0, DISP_OFFSET * 2, 4);

  delay(1000);

}