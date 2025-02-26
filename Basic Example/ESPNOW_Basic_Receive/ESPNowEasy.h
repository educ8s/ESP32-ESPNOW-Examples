// ESPNowEasy.h
#ifndef ESPNowEasy_h
#define ESPNowEasy_h

#include <esp_now.h>
#include <WiFi.h>
#include "esp_wifi.h"  // Make sure this is included

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
    static void receiveCallback(const esp_now_recv_info_t* recv_info, const uint8_t* data, int len);
};

#include "ESPNowEasy.cpp"
#endif