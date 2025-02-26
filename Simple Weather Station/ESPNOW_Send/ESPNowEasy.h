// ESPNowEasy.h
#ifndef ESPNowEasy_h
#define ESPNowEasy_h

#include <esp_now.h>
#include <WiFi.h>

template<typename MessageType>
class ESPNowEasy {
public:
    typedef void (*ReceiverCallback)(MessageType& message);
    
    bool begin();
    bool send(MessageType& message);
    void onReceive(ReceiverCallback callback);
    
private:
    uint8_t broadcastAddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    static ReceiverCallback userCallback;
    static void receiveCallback(const uint8_t* mac, const uint8_t* data, int len);
};

#include "ESPNowEasy.cpp"
#endif