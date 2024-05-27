#include <M5Core2.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>

// Create an instance for the SHT31 sensor
Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup() {
  // Initialize the M5Stack Core2
  M5.begin();
  M5.Lcd.setTextSize(2);

  // Initialize the I2C communication
  Wire.begin();

  // Initialize the SHT31 sensor
  if (!sht31.begin(0x44)) {   // Set to 0x45 for alternate I2C address
    M5.Lcd.drawString("Could not find a valid SHT31 sensor, check wiring!", 10, 10, 2);
    while (1);
  }

  // Print the labels
  M5.Lcd.drawString("Temperature:", 10, 10, 2);
  M5.Lcd.drawString("Humidity:", 10, 40, 2);
}

void loop() {
  // Read the values from the SHT31 sensor
  float temperatureC = sht31.readTemperature();
  float humidity = sht31.readHumidity();

  // Convert temperature from Celsius to Fahrenheit
  float temperatureF = temperatureC * 9.0 / 5.0 + 32.0;

  // Update the temperature value
  String tempStr = String(temperatureF, 2) + " F";
  int offset = 30; // Offset from the right side of the screen
  M5.Lcd.fillRect(M5.Lcd.width() - M5.Lcd.textWidth(tempStr) - offset, 10, M5.Lcd.textWidth(tempStr) + offset, 30, BLACK);
  M5.Lcd.drawString(tempStr, M5.Lcd.width() - M5.Lcd.textWidth(tempStr) - offset, 10, 2);

  // Update the humidity value
  String humStr = String(humidity, 2) + " %";
  M5.Lcd.fillRect(M5.Lcd.width() - M5.Lcd.textWidth(humStr) - offset, 40, M5.Lcd.textWidth(humStr) + offset, 30, BLACK);
  M5.Lcd.drawString(humStr, M5.Lcd.width() - M5.Lcd.textWidth(humStr) - offset, 40, 2);

  // Wait for a second before reading the values again
  delay(1000);
}