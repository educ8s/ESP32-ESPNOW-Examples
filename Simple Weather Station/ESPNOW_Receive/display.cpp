#include "Display.h"

// Constructor
Display::Display() : tft(TFT_CS, TFT_DC, TFT_RST) {}

// Initialize the display and backlight, then draw the static UI
void Display::begin() {
    tft.begin();
    tft.setRotation(0); // **Portrait Orientation**
    tft.fillScreen(ILI9341_BLACK);
    drawUI(); // Draw static UI elements
}

void Display::update(float temperature, float humidity, float pressure) {
    char tempStr[10], humStr[10], pressStr[10];

    snprintf(tempStr, sizeof(tempStr), "%.1f", temperature);
    snprintf(humStr, sizeof(humStr), "%.1f", humidity);
    snprintf(pressStr, sizeof(pressStr), "%.1f", pressure);

    updateValue(tempStr, ILI9341_WHITE, 60, ILI9341_RED, 60);    // **Temperature Section**
    updateValue(humStr, ILI9341_WHITE, 170, ILI9341_BLUE, 60);   // **Humidity Section**
    updateValue(pressStr, ILI9341_WHITE, 280, ILI9341_GREEN, 50); // **Pressure Section**
}


// **Helper function to print text centered horizontally**
void Display::printCenteredText(const char* text, uint16_t color, int y, int textSize) {
    int16_t x1, y1;
    uint16_t w, h;
    tft.setTextSize(textSize);
    tft.setTextColor(color);
    tft.getTextBounds(text, 0, y, &x1, &y1, &w, &h);
    tft.setCursor((tft.width() - w) / 2, y);
    tft.print(text);
}

void Display::drawUI() {
    // **Temperature Section**
    tft.fillRect(0, 0, 240, 100, ILI9341_RED);
    printCenteredText("TEMPERATURE", ILI9341_WHITE, 20, 2);

    // **Humidity Section**
    tft.fillRect(0, 110, 240, 100, ILI9341_BLUE);
    printCenteredText("HUMIDITY", ILI9341_WHITE, 130, 2);

    // **Pressure Section**
    tft.fillRect(0, 220, 240, 100, ILI9341_GREEN);
    printCenteredText("PRESSURE", ILI9341_WHITE, 240, 2);

    // **Draw Unit Labels Once**
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE);

    // **Temperature "°C"**
    tft.setCursor(150, 58);
    tft.print("o"); // Small "o" for degree
    tft.setTextSize(3);
    tft.setCursor(165, 60);
    tft.print("C");

    // **Humidity "%"**
    tft.setCursor(160, 170);
    tft.print("%");

    // **Pressure "hPa"**
    tft.setCursor(160, 280);
    tft.print("hPa");
}

// **Update only the numeric values (aligned to the left of units)**
void Display::updateValue(const char* value, uint16_t color, int y, uint16_t bgColor, int xPosition) {
    tft.fillRect(xPosition, y, 90, 30, bgColor); // Clear previous value
    tft.setTextSize(3);
    tft.setTextColor(color);
    tft.setCursor(xPosition, y);
    tft.print(value); // Print updated value next to static text
}

