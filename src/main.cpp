#include <M5Core2.h>

void setup() {
  // Initialize M5Stack Core2
  M5.begin();

  // Set up the display
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  // Get screen dimensions
  int screenWidth = M5.Lcd.width();
  int screenHeight = M5.Lcd.height();

  // Define the text
  const char* text = "Hello, World!";

  // Calculate the width and height of the text
  int16_t textWidth = M5.Lcd.textWidth(text);
  int16_t textHeight = M5.Lcd.fontHeight();

  // Calculate the position to center the text
  int16_t x = (screenWidth - textWidth) / 2;
  int16_t y = (screenHeight - textHeight) / 2;

  // Print the centered text to the screen
  M5.Lcd.setCursor(x, y);
  M5.Lcd.println(text);
}

void loop() {
  // Nothing to do in the loop
}
