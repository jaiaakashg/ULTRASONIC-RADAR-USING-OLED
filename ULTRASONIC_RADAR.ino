#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NewPing.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIG_PIN 2
#define ECHO_PIN 3
#define MAX_DISTANCE 200 

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  unsigned int distance = sonar.ping_cm();

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Distance Radar");

  display.setCursor(0, 10);
  display.print("Distance: ");
  display.print(distance);
  display.print(" cm");

  int barLength = map(distance, 0, MAX_DISTANCE, 0, SCREEN_WIDTH);
  display.fillRect(0, 30, barLength, 10, SSD1306_WHITE);

  display.display();

  delay(100);
}

