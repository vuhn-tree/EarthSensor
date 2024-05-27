#include <M5Core2.h>
#include <Wire.h>
#include "SHT31.h"
#include "QMP6988.h"

// Create instances for SHT30 and QMP6988 sensors
SHT31 sht30;
QMP6988 qmp6988;

void setup() {
  // Initialize the M5Stack Core2
  M5.begin();
  M5.Lcd.setTextSize(2);

  // Initialize the I2C communication
  Wire.begin();

  // Initialize the SHT30 sensor
  if (!sht30.begin(0x44)) {
    M5.Lcd.println("Could not find a valid SHT30 sensor, check wiring!");
    while (1);
  }

  // Initialize the QMP6988 sensor
  if (!qmp6988.init()) {
    M5.Lcd.println("Could not find a valid QMP6988 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  // Read the values from the SHT30 sensor
  float temperature = sht30.readTemperature();
  float humidity = sht30.readHumidity();

  // Read the value from the QMP6988 sensor
  float pressure = qmp6988.calcPressure();

  // Clear the screen
  M5.Lcd.fillScreen(BLACK);

  // Display the sensor values on the screen
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.printf("Temperature: %.2f C", temperature);
  
  M5.Lcd.setCursor(10, 40);
  M5.Lcd.printf("Humidity: %.2f %%", humidity);
  
  M5.Lcd.setCursor(10, 70);
  M5.Lcd.printf("Pressure: %.2f hPa", pressure / 100.0F);

  // Wait for a second before reading the values again
  delay(1000);
}
