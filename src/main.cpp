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
    M5.Lcd.println("Could not find a valid SHT31 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  // Read the values from the SHT31 sensor
  float temperature = sht31.readTemperature();
  float humidity = sht31.readHumidity();

  // Clear the screen
  M5.Lcd.fillScreen(BLACK);

  // Display the sensor values on the screen
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.printf("Temperature: %.2f C", temperature);
  
  M5.Lcd.setCursor(10, 40);
  M5.Lcd.printf("Humidity: %.2f %%", humidity);

  // Wait for a second before reading the values again
  delay(1000);
}
