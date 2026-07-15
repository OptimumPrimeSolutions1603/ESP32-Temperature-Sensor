#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 4
#define DHTTYPE DHT11

#define GREEN_LED 5
#define RED_LED 19
#define YELLOW_LED 18

DHT dht(DHTPIN, DHTTYPE);

void greenLight()
{
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void yellowLight()
{
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(RED_LED, LOW);
}

void redLight()
{
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, HIGH);
}
void updateDisplay(float temperature, float humidity)
{
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("Temperature");

  display.setTextSize(1);
  display.setCursor(0, 15);
  display.print(temperature);
  display.print(" ");
  display.print((char)247);
  display.print("C");

  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print("Humidity");

  display.setTextSize(1.5);
  display.setCursor(0, 45);
  display.print(humidity);
  display.print(" %");

  display.display();
}

void ledGlow(float temperature)
{
  if(temperature<27.5)
    greenLight();

  else if(temperature>=27.5 && temperature<28)
    yellowLight();

  else
    redLight();
}
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  dht.begin();

}

void loop() {
  float temperature=dht.readTemperature();
  float humidity=dht.readHumidity();

  updateDisplay(temperature, humidity);
  ledGlow(temperature);
  delay(2000);

}

