#include <Arduino.h>
#include "../include/tasks.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <ESP32_blelib.hh>

extern QueueHandle_t respondQueue;

void comHandler(void *arg){
    float respond = 0;
    pinMode(LED_BUILTIN, OUTPUT);
    ESP32_blelib::init(&pCharacteristicTX,&pCharacteristicRX);
    while(1){
        if(xQueueReceive(respondQueue, &respond, pdMS_TO_TICKS(100)) == pdPASS){
            pCharacteristicTX.setValue(respond);
            pCharacteristicTX.notify();
        }
    }
}