#include <M5Core2.h>

void setup() {
  // Initialize M5Stack Core2
  M5.begin();

  // Set up the display
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 0);

  // Print "Hello, World!" to the screen
  M5.Lcd.println("Hello, World!");
}

void loop() {
  // Nothing to do in the loop
}