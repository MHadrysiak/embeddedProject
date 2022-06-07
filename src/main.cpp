#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <ESP32_blelib.hh>
#include "../include/tasks.h"
#include "freertos/FreeRTOS.h"


QueueHandle_t pwmQueue, comQueue, respondQueue;

void setup(){
    Serial.begin(115200);
    
    pwmQueue = xQueueCreate(10, sizeof(int));
    comQueue = xQueueCreate(10, sizeof(char[15]));
    respondQueue = xQueueCreate(10, sizeof(float));

    xTaskCreatePinnedToCore(tempHandler, "Temperature handling task", 8192, NULL, 1, NULL, PRO_CPU_NUM);
    xTaskCreatePinnedToCore(motorHandler, "Motor handling task", 8192, NULL, 5, NULL, PRO_CPU_NUM);
    xTaskCreatePinnedToCore(comHandler, "Communication handling task", 8192, NULL, 1, NULL, PRO_CPU_NUM);
      
}

void loop(){
}
