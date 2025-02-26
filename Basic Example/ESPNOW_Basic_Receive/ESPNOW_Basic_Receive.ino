#include <ESPNowEasy.h>

struct Message {
    int counter;
    char text[32];
};

ESPNowEasy<Message> espNow;

void onMessageReceived(Message& receivedMessage) {
    Serial.print("Received Data -> Counter: ");
    Serial.print(receivedMessage.counter);
    Serial.print(", Message: ");
    Serial.println(receivedMessage.text);
}

void setup() {
    Serial.begin(115200); 
    espNow.begin();
    espNow.onReceive(onMessageReceived); 
}

void loop() {
    // Receiver loop is empty for this basic example.
}