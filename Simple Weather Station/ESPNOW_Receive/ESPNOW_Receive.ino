#include <ESPNowEasy.h>
#include "Display.h"

struct WeatherData {
    float temperature;
    float humidity;
    float pressure;
};

ESPNowEasy<WeatherData> espNow;
Display display;

void onWeatherDataReceived(WeatherData& data) {
    Serial.println("🔹 Received Weather Data:");
    Serial.print("🌡 Temperature: ");
    Serial.print(data.temperature);
    Serial.println(" °C");

    Serial.print("💧 Humidity: ");
    Serial.print(data.humidity);
    Serial.println(" %");

    Serial.print("📡 Pressure: ");
    Serial.print(data.pressure);
    Serial.println(" hPa");

    Serial.println("-----------------------------------");

    // Update the display with new data
    display.update(data.temperature, data.humidity, data.pressure);
}

void setup() {
    Serial.begin(115200);

    if (!espNow.begin()) {
        Serial.println("❌ ESP-NOW Initialization failed!");
        return;
    }

    espNow.onReceive(onWeatherDataReceived);
    Serial.println("✅ ESP-NOW Receiver Ready...");

    display.begin();
}

void loop() {
    // The ESPNowEasy library automatically calls onWeatherDataReceived when data arrives.
}
