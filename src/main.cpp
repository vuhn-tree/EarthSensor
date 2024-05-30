#include <M5Core2.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <vector>
// #include <TFT_eSPI.h>       // Include the graphics library (this includes the font library)
#include <Free_Fonts.h>     // Include the header file for free fonts

// Create an instance for the SHT31 sensor
Adafruit_SHT31 sht31 = Adafruit_SHT31();

// Graph settings
const int GRAPH_X = 10;
const int GRAPH_Y = 100;
const int GRAPH_HEIGHT = 100;
const int GRAPH_LINES = 5;
int graphWidth;
std::vector<float> temperatureData;
int dataPointIndex = 0;

// Brightness settings
const int BRIGHTNESS_LEVELS[] = {64, 128, 192, 255}; // Define brightness levels
int currentBrightnessIndex = 0;

// Timing
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 1000; // Interval for updating the display and reading sensor data

// Function prototypes
void initializeSystem();
void updateDisplay(float temperature, float humidity);
void drawGraph();
void updateGraphData(float temperature);
void cycleBrightness();

void setup() {
  initializeSystem();
}

void loop() {
  M5.update(); // Update button states

  // Check if button C is pressed to cycle brightness
  if (M5.BtnC.wasPressed()) {
    cycleBrightness();
  }

  // Check if it's time to update the display and sensor data
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;

    // Read the values from the SHT31 sensor
    float temperatureC = sht31.readTemperature();
    float humidity = sht31.readHumidity();
    float temperatureF = temperatureC * 9.0 / 5.0 + 32.0;

    // Update the display and graph
    updateDisplay(temperatureF, humidity);
    updateGraphData(temperatureF);
    drawGraph();
  }
}

void initializeSystem() {
  // Initialize the M5Stack Core2
  M5.begin();
  M5.Lcd.fillScreen(BLACK);

  // Initialize the I2C communication
  Wire.begin();

  // Initialize the SHT31 sensor
  if (!sht31.begin(0x44)) {   // Set to 0x45 for alternate I2C address
    M5.Lcd.setTextColor(RED);
    M5.Lcd.setFreeFont(&FreeSansBold12pt7b);
    M5.Lcd.drawString("Could not find a valid SHT31 sensor, check wiring!", 10, 10);
    while (1);
  }

  // Set font and print the labels
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setFreeFont(&FreeSansBold12pt7b);
  M5.Lcd.drawString("Temperature:", 10, 10);
  M5.Lcd.drawString("Humidity:", 10, 40);

  // Initialize the graph width and temperature data vector
  graphWidth = M5.Lcd.width() - 2 * GRAPH_X;
  temperatureData.resize(graphWidth, 0);

  // Draw the graph frame and lines
  M5.Lcd.drawRect(GRAPH_X, GRAPH_Y, graphWidth, GRAPH_HEIGHT, WHITE);
  for (int i = 1; i <= GRAPH_LINES; i++) {
    int lineY = GRAPH_Y + i * (GRAPH_HEIGHT / (GRAPH_LINES + 1));
    M5.Lcd.drawLine(GRAPH_X, lineY, GRAPH_X + graphWidth, lineY, LIGHTGREY);
  }

  // Set initial brightness
  M5.Axp.ScreenBreath(BRIGHTNESS_LEVELS[currentBrightnessIndex]);
}

void updateDisplay(float temperature, float humidity) {
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setFreeFont(&FreeSansBold12pt7b);
  String tempStr = String(temperature, 2) + " F";
  String humStr = String(humidity, 2) + " %";
  int offset = 30; // Offset from the right side of the screen

  M5.Lcd.fillRect(M5.Lcd.width() - M5.Lcd.textWidth(tempStr) - offset, 10, M5.Lcd.textWidth(tempStr) + offset, 30, BLACK);
  M5.Lcd.drawString(tempStr, M5.Lcd.width() - M5.Lcd.textWidth(tempStr) - offset, 10);

  M5.Lcd.fillRect(M5.Lcd.width() - M5.Lcd.textWidth(humStr) - offset, 40, M5.Lcd.textWidth(humStr) + offset, 30, BLACK);
  M5.Lcd.drawString(humStr, M5.Lcd.width() - M5.Lcd.textWidth(humStr) - offset, 40);
}

void drawGraph() {
  M5.Lcd.fillRect(GRAPH_X + 1, GRAPH_Y + 1, graphWidth - 2, GRAPH_HEIGHT - 2, BLACK);
  M5.Lcd.setTextColor(CYAN);
  for (int i = 1; i < graphWidth; i++) {
    int x1 = GRAPH_X + i - 1;
    int y1 = GRAPH_Y + GRAPH_HEIGHT - (temperatureData[(dataPointIndex + i - 1) % graphWidth] - 32) * (GRAPH_HEIGHT - 2) / 100;
    int x2 = GRAPH_X + i;
    int y2 = GRAPH_Y + GRAPH_HEIGHT - (temperatureData[(dataPointIndex + i) % graphWidth] - 32) * (GRAPH_HEIGHT - 2) / 100;
    M5.Lcd.drawLine(x1, y1, x2, y2, CYAN);
  }
}

void updateGraphData(float temperature) {
  temperatureData[dataPointIndex] = temperature;
  dataPointIndex = (dataPointIndex + 1) % graphWidth;
}

void cycleBrightness() {
  currentBrightnessIndex = (currentBrightnessIndex + 1) % (sizeof(BRIGHTNESS_LEVELS) / sizeof(BRIGHTNESS_LEVELS[0]));
  M5.Axp.ScreenBreath(BRIGHTNESS_LEVELS[currentBrightnessIndex]);
}
