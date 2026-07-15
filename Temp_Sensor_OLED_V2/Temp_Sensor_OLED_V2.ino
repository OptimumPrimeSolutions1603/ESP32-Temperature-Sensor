#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void updateDisplay(float temperature, float humidity)
{
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("Temperature");

  display.setTextSize(1.5);
  display.setCursor(0, 15);
  display.print(temperature);
  display.print(" C");

  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("Humidity");

  display.setTextSize(1.5);
  display.setCursor(0, 45);
  display.print(humidity);

  display.display();
}
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  dht.begin();

}

void loop() {
  float temperature=dht.readTemperature();
  float humidity=dht.readHumidity();

  updateDisplay(temperature, humidity);
  delay(2000);

}
