#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Define SPI Pins for ILI9341 (update if needed)
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4

class Display {
public:
    Display();
    void begin();
    void drawUI();
    void update(float temperature, float humidity, float pressure);

private:
    Adafruit_ILI9341 tft;
    void printCenteredText(const char* text, uint16_t color, int y, int textSize);
    void updateValue(const char* value, uint16_t color, int y, uint16_t bgColor, int xPosition);
};
