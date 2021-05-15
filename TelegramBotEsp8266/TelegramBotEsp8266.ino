#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "TelegramBot.h"

const char* ssid = "YourWifiSSID";
const char* password = "YourPassword";
const char botToken[] = "yourBotToken:yourBotHash";
const String chatId = "yourChatId";
const String sticker1 = "CAACAgIAAxkBAAEBU0hfXOaLy_bjVXgsKJGcYUCdTtDMPgACTAEAAhAhAhCZ8EMfwrO_ZBsE";
const String sticker2 = "CAACAgIAAxkBAAEBU0pfXOar2Vut-Dd1vhCVyVDEBguVngACUAEAAhAhAhBL3OvxWIxXrxsE";

int lastPinState = LOW;
int inputPin = 5;
WiFiClientSecure httpClient;
TelegramBot bot(botToken, httpClient);

void connectToWifi() {
    if (WiFi.status() == WL_CONNECTED) {
        return;
    }

    Serial.print("Connecting to Wifi: ");
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("Connected to Wifi.");
}

void sendMessageIfNeeded() {
    int value = digitalRead(inputPin);
    
    if (value == lastPinState) {
        return;
    } else {
        lastPinState = value;
        
        if (value == HIGH) {
            bot.sendMessage(chatId, "Chicken!");
            bot.sendSticker(chatId, sticker1);
        } else {
            bot.sendMessage(chatId, "The other chicken!");
            bot.sendSticker(chatId, sticker2);
        }
    }
}

void setup() {
    Serial.begin(115200);
    while (!Serial);
    pinMode(inputPin, INPUT);
    connectToWifi();
    bot.begin();
}

void loop() {
    connectToWifi();
    sendMessageIfNeeded();
    delay(1000);
}
