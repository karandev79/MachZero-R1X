#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    8
#define TFT_DC     9

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

uint16_t eyeColor = ST7735_WHITE;
uint16_t pupilColor = ST7735_BLACK;
int eyeRadius = 30;
int pupilRadius = 12;

void setup() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST7735_BLACK); 
}

void loop() {
  int action = random(0, 10);

  if (action < 2) {
    blinkEyes();
  } else if (action < 5) {
    lookAround();
  } else {
    drawEyes(0, 0);
    delay(1500);
  }
}

void drawEyes(int offsetX, int offsetY) {
  tft.fillScreen(ST7735_BLACK);
  
  tft.fillCircle(45, 64, eyeRadius, eyeColor);
  tft.fillCircle(45 + offsetX, 64 + offsetY, pupilRadius, pupilColor);
  
  tft.fillCircle(115, 64, eyeRadius, eyeColor);
  tft.fillCircle(115 + offsetX, 64 + offsetY, pupilRadius, pupilColor);
}

void blinkEyes() {
  tft.fillScreen(ST7735_BLACK);
  tft.fillRect(15, 60, 60, 8, ST7735_WHITE);
  tft.fillRect(85, 60, 60, 8, ST7735_WHITE);
  delay(150);
  drawEyes(0, 0);
}

void lookAround() {
  drawEyes(-10, 0);
  delay(800);
  drawEyes(10, 0);
  delay(800);
  drawEyes(0, -10);
  delay(800);
  drawEyes(0, 0); 
}