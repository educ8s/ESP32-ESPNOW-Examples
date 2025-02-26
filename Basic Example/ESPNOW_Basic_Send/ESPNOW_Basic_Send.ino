#include <ESPNowEasy.h>

struct Message { 
    int counter;
    char text[32]; 
};

ESPNowEasy<Message> espNow; 
Message dataToSend;

void setup() {
    espNow.begin();
    dataToSend = {0, "Hello World!"};
}

void loop() {
    espNow.send(dataToSend);
    dataToSend.counter++;
    delay(1000); 
}