#include <Arduino.h>
#include "../include/tasks.h"

std::string message;
std::string data;
extern QueueHandle_t comQueue;
extern QueueHandle_t pwmQueue;

void motorHandler(void *arg){
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);
    digitalWrite(ENABLE_A, HIGH);
    ledcSetup(CHANNEL, FREQ, RES);
    ledcAttachPin(ENABLE_A, CHANNEL);
    ledcAttachPin(ENABLE_B, CHANNEL);
    int flag = 0;
    int dutyCycle = 0;
    while(1){
        xQueueReceive(comQueue, &data, pdMS_TO_TICKS(100));
        xQueueReceive(pwmQueue, &flag, pdMS_TO_TICKS(100));
        Serial.println(flag);
        dutyCycle = 50 * (flag - STANDARD_TEMPERATURE);
        if(dutyCycle > 255) dutyCycle = 250;
        //Serial.println(data.c_str());
        if(data == "START"){
            digitalWrite(IN_1, HIGH);
            digitalWrite(IN_2, LOW);
            ledcWrite(CHANNEL, dutyCycle);
            Serial.println(dutyCycle);

            // for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
            //     ledcWrite(CHANNEL, dutyCycle);
            //     delay(15);
            // }

            // for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
            //     ledcWrite(CHANNEL, dutyCycle);   
            //     delay(15);
            // }
        }else if (data == "STOP"){
            digitalWrite(IN_1, LOW);
            digitalWrite(IN_2, LOW);
        }
        delay(1000);
    }
}