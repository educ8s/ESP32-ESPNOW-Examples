#ifndef ESPNowEasy_cpp
#define ESPNowEasy_cpp

#include "ESPNowEasy.h"

template<typename MessageType>
typename ESPNowEasy<MessageType>::ReceiverCallback ESPNowEasy<MessageType>::userCallback = nullptr;

template<typename MessageType>
bool ESPNowEasy<MessageType>::begin() {
    WiFi.mode(WIFI_STA);

    esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_LR);

    if (esp_now_init() != ESP_OK) {
        return false;
    }
    
    esp_now_peer_info_t peer;
    memcpy(peer.peer_addr, broadcastAddress, 6);
    peer.channel = 0;
    peer.encrypt = false;
    
    if (esp_now_add_peer(&peer) != ESP_OK) {
        return false;
    }
    
    return true;
}

template<typename MessageType>
bool ESPNowEasy<MessageType>::send(MessageType& message) {
    bool success = (esp_now_send(broadcastAddress, (uint8_t*)&message, sizeof(MessageType)) == ESP_OK);
    if (success) {
        Serial.println("Message Sent Successfully");
    } else {
        Serial.println("Message Failed!");
    }
    return success;
}

template<typename MessageType>
void ESPNowEasy<MessageType>::onReceive(ReceiverCallback callback) {
    userCallback = callback;
    esp_now_register_recv_cb(receiveCallback);
}

template<typename MessageType>
void ESPNowEasy<MessageType>::receiveCallback(const esp_now_recv_info_t* recv_info, const uint8_t* data, int len) {
    if (len >= sizeof(MessageType) && userCallback != nullptr) {
        MessageType message;
        memcpy(&message, data, sizeof(MessageType));
        userCallback(message);
    }
}

#endif