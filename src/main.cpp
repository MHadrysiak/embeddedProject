#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include <ESP32_blelib.hh>
#include "../include/tasks.h"
#include "freertos/FreeRTOS.h"



QueueHandle_t pwmQueue;
QueueHandle_t comQueue;
QueueHandle_t respondQueue;
int echoNumber = 0;


int i = 0;
// void respond(std::string send_message)
// {
//     Serial.println("inside send_message");
//     pCharacteristicTX.setValue(send_message);
//     pCharacteristicTX.notify();
//     Serial.println("sent send_message");
// }

void setup(){
    Serial.begin(115200);
    Serial.println("wtf");
    // bled.init(&pCharacteristicTX,&pCharacteristicRX);
    
    pwmQueue = xQueueCreate(10, sizeof(int));
    comQueue = xQueueCreate(10, sizeof(char[15]));
    respondQueue = xQueueCreate(10, sizeof(float));



    xTaskCreatePinnedToCore(tempHandler, "Temperature handling task", 8192, NULL, 1, NULL, PRO_CPU_NUM);
    xTaskCreatePinnedToCore(motorHandler, "Motor handling task", 8192, NULL, 5, NULL, PRO_CPU_NUM);
    xTaskCreatePinnedToCore(comHandler, "Communication handling task", 8192, NULL, 1, NULL, PRO_CPU_NUM);
    pinMode(LED_BUILTIN, OUTPUT);
      
}

void loop(){

    // delay(10000);
    // String text = "";
    // text = milliVolt;
    // respond(text.c_str());
}
