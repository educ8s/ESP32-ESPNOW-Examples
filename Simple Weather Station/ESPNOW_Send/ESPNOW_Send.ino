#include <ESPNowEasy.h>
#include "sensor.h"

struct WeatherData {
    float temperature;
    float humidity;
    float pressure;
};

ESPNowEasy<WeatherData> espNow;
Sensor sensor(true); // Use metric system

void setup() {
    Serial.begin(115200);

    if (!espNow.begin()) {
        Serial.println("ESP-NOW Initialization failed!");
        return;
    }

    if (!sensor.begin()) {
        Serial.println("BME280 sensor not found!");
        return;
    }

    Serial.println("ESP-NOW Sender with BME280 Ready...");
}

void loop() {
    WeatherData dataToSend;
    dataToSend.temperature = sensor.getTemperature();
    dataToSend.humidity = sensor.getHumidity();    
    dataToSend.pressure = sensor.getPressure();

    Serial.print("Sending Data -> Temp: ");
    Serial.print(dataToSend.temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(dataToSend.humidity);
    Serial.print("%, Pressure: ");
    Serial.print(dataToSend.pressure);
    Serial.println(" hPa");

    espNow.send(dataToSend);

    delay(2000);
}
