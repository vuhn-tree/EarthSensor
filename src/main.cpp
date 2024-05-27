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

  // Clear only the value areas to update them
  M5.Lcd.fillRect(180, 10, 130, 30, BLACK);  // Clear the previous temperature value
  M5.Lcd.fillRect(180, 40, 130, 30, BLACK);  // Clear the previous humidity value

  // Update the temperature value
  M5.Lcd.drawString(String(temperatureF, 2) + " F", 310 - M5.Lcd.textWidth(String(temperatureF, 2) + " F"), 10, 2);

  // Update the humidity value
  M5.Lcd.drawString(String(humidity, 2) + " %", 310 - M5.Lcd.textWidth(String(humidity, 2) + " %"), 40, 2);

  // Wait for a second before reading the values again
  delay(1000);
}
