#include "TelegramBot.h"

TelegramBot::TelegramBot(const char* token, WiFiClientSecure &client) {
    this -> client = & client;
    this -> token = token;
}

void TelegramBot::begin() {
    if (!client -> connected()) {
        client -> setInsecure();
        
        if (!client -> connect(HOST, PORT)) {
            Serial.println("Connection failed.");
        } else {
            Serial.println("Connected to API.");
        }
    }
}

String TelegramBot::sendMessage(String chatId, String text) {
    if (chatId != "0" && chatId != "") {
        StaticJsonDocument < JSON_BUFFER_SIZE > jsonBuffer;
        jsonBuffer["chat_id"] = chatId;
        jsonBuffer["text"] = text;
        String message;
        serializeJson(jsonBuffer, message);
        return postMessage(message);
    } else {
        Serial.println("Chat id not defined.");
    }
}

String TelegramBot::sendSticker(String chatId, String sticker) {
    if (chatId != "0" && chatId != "") {
        StaticJsonDocument < JSON_BUFFER_SIZE > jsonBuffer;
        jsonBuffer["chat_id"] = chatId;
        jsonBuffer["sticker"] = sticker;
        String message;
        serializeJson(jsonBuffer, message);
        return postSticker(message);
    } else {
        Serial.println("Chat id not defined.");
    }
}

String TelegramBot::postMessage(String message) {
    begin();
    client -> println("POST /bot" + String(token) + "/sendMessage HTTP/1.1");
    client -> println("Host: api.telegram.org");
    client -> println("Content-Type: application/json");
    client -> println("User-Agent: NodeMCU");
    client -> println("Connection: close");
    client -> print("Content-Length: ");
    client -> println(message.length());
    client -> println();
    client -> println(message);
    return readPayload();
}

String TelegramBot::postSticker(String sticker) {
    begin();
    client -> println("GET /bot" + String(token) + "/sendSticker HTTP/1.1");
    client -> println("Host: api.telegram.org");
    client -> println("Content-Type: application/json");
    client -> println("User-Agent: NodeMCU");
    client -> println("Connection: close");
    client -> print("Content-Length: ");
    client -> println(sticker.length());
    client -> println();
    client -> println(sticker);
    return readPayload();
}

String TelegramBot::readPayload() {
    char c;
    String payload = "";
    while (client -> connected()) {
        payload = client -> readStringUntil('\n');
        
        if (payload == "\r") {
            Serial.println("Headers received.");
            break;
        }
    }
    
    payload = client -> readStringUntil('\r');
    return payload;
}
