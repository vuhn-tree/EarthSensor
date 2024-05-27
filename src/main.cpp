#include <M5Core2.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define the dimensions of the OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define the OLED reset pin (if applicable)
#define OLED_RESET -1

// Create an OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Initialize M5Stack Core2
  M5.begin();

  // Initialize the OLED display
  if(!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();

  // Set text color and size
  display.setTextColor(SSD1306_YELLOW);
  display.setTextSize(1);

  // Get screen dimensions
  int screenWidth = display.width();
  int screenHeight = display.height();

  // Define the text
  const char* text = "Hello World";

  // Calculate the width and height of the text
  int16_t x1, y1;
  uint16_t textWidth, textHeight;
  display.getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &textHeight);

  // Calculate the position to center the text
  int16_t x = (screenWidth - textWidth) / 2;
  int16_t y = (screenHeight - textHeight) / 2;

  // Print the centered text to the screen
  display.setCursor(x, y);
  display.print(text);

  // Display the text
  display.display();
}

void loop() {
  // Nothing to do in the loop
}
