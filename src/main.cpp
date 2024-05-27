#include <M5Core2.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define the dimensions of the OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define the OLED I2C address
#define OLED_I2C_ADDRESS 0x3C

// Define the OLED reset pin (if applicable)
#define OLED_RESET -1

// Create an OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define the text
const char* text = "Hello World";

void setup() {
  // Initialize M5Stack Core2
  M5.begin();

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();

  // Set text color and size
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
}

void loop() {
  // Clear the display buffer
  display.clearDisplay();

  // Get screen dimensions
  int screenWidth = display.width();
  int screenHeight = display.height();

  // Calculate the width and height of the text
  int16_t x1, y1;
  uint16_t textWidth, textHeight;
  display.getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &textHeight);

  // Scroll the text horizontally
  static int16_t x = screenWidth;
  display.setCursor(x, (screenHeight - textHeight) / 2);
  display.print(text);
  display.display();

  // Move text to the left
  x -= 1;
  if (x < -textWidth) {
    x = screenWidth;
  }

  // Add a small delay to control the speed of the scrolling
  delay(25);
}
