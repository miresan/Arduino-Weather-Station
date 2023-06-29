#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <DHT.h>

#define TFT_CS   10
#define TFT_RST  8
#define TFT_DC   9
#define DHTPIN 7       // Pin where the DHT11 is connected

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
DHT dht(DHTPIN, DHT11); // Initialize the DHT11 sensor

void setup() {
  Serial.begin(9600);   // Initialize serial communication
  dht.begin();          // Start the DHT11 sensor
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(3);
  tft.fillScreen(ST7735_BLACK);
}

void loop() {
  // Read sensor values
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit the loop if so
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the readings to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C");
  Serial.print(" Humidity: ");
  Serial.print(humidity);
  Serial.print("%");
  Serial.println();

  // Clear the display
  tft.fillScreen(ST7735_WHITE);

  // Set the text color and size
  tft.setTextColor(ST7735_BLACK);
  tft.setTextSize(1);

  // Calculate the center position of the display
  int16_t centerX = tft.width() / 2;
  int16_t centerY = tft.height() / 2;

  // Display temperature
  String tempText = "T: " + String(temperature, 1) + " \367C";
  int16_t tempTextWidth = tempText.length() * 6; // Estimate width based on character count
  int16_t tempX = centerX - tempTextWidth / 2;
  int16_t tempY = centerY - 10; // Adjust Y position based on text size
  tft.setCursor(tempX, tempY);
  tft.print(tempText);

  // Display humidity
  String humText = "H: " + String(humidity, 1) + "%";
  int16_t humTextWidth = humText.length() * 6; // Estimate width based on character count
  int16_t humX = centerX - humTextWidth / 2;
  int16_t humY = centerY + 10; // Adjust Y position based on text size
  tft.setCursor(humX, humY);
  tft.print(humText);

  delay(2000);  // Wait for 2 seconds before taking the next reading
}
