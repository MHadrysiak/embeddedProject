#include <BLEServer.h>
#include <BLEUtils.h>

static bool deviceConnected;

class EchoServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        deviceConnected = true;
        // stop advt?
        Serial.println("Connected!");
        digitalWrite(2, HIGH);
    };

    void onDisconnect(BLEServer *pServer)
    {
        // restart advt?
        deviceConnected = false;
        Serial.println("Disconnected!");
        pServer->getAdvertising()->start();
        digitalWrite(2, LOW);
    }
};