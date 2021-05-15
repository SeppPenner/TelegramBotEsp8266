#ifndef TelegramBot_h
#define TelegramBot_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

#define HOST "api.telegram.org"
#define PORT 443

#ifndef JSON_BUFFER_SIZE
#ifdef ESP8266
#define JSON_BUFFER_SIZE 1000
#else
#define JSON_BUFFER_SIZE 10000
#endif
#endif

class TelegramBot {
    public:
        TelegramBot(const char* token, WiFiClientSecure &client);
        void begin();
        String sendMessage(String chatId, String text);
        String sendSticker(String chatId, String sticker);
    private:
        String readPayload();
        String postMessage(String message);
        String postSticker(String sticker);
        const char* token;
        WiFiClientSecure* client;
};

#endif
