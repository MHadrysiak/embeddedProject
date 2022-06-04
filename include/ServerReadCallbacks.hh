#include <BLEServer.h>
#include <BLEUtils.h>

extern std::string message;
// std::string kupa;
extern QueueHandle_t comQueue;

static bool messageReceivedComplete;

class ServerReadCallbacks : public BLECharacteristicCallbacks
{
public:
        void onWrite(BLECharacteristic *pCharacteristic)
    {
        std::string rxValue = pCharacteristic->getValue();
        Serial.println("*********");
        Serial.print("Received Value: ");
        for (int i = 0; i < rxValue.length(); i++)
        {
            Serial.print(rxValue[i]);
        }
        Serial.println();

        // add to message (as of now just one packet)
        message = rxValue;
        xQueueSend(comQueue, &message, portMAX_DELAY);

        // once you think all packets are received. As of now one packet
        messageReceivedComplete = true;
        // respond(rxValue);
        // while (1)
        //     if (Serial2.availableForWrite())
        //     {
        //         Serial2.write(rxValue.c_str(), rxValue.length() + 1);
        //         Serial.println("wrote to tanwa");
        //         break;
        //     }
    }
};