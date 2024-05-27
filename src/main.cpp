#include <M5Core2.h>
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"

// Create an instance of the BME280 sensor
Adafruit_BME280 bme;

void setup() {
  // Initialize the M5Stack Core2
  M5.begin();
  M5.Lcd.setTextSize(2);

  // Initialize the I2C communication on port A
  Wire.begin(21, 22); // SDA is on pin 21, SCL is on pin 22 for port A

  // Initialize the BME280 sensor
  if (!bme.begin(0x76)) {
    M5.Lcd.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  // Read the values from the sensor
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  // Clear the screen
  M5.Lcd.fillScreen(BLACK);

  // Display the sensor values on the screen
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.printf("Temperature: %.2f C", temperature);
  
  M5.Lcd.setCursor(10, 40);
  M5.Lcd.printf("Humidity: %.2f %%", humidity);
  
  M5.Lcd.setCursor(10, 70);
  M5.Lcd.printf("Pressure: %.2f hPa", pressure);

  // Wait for a second before reading the values again
  delay(1000);
}
