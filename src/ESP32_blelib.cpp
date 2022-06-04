#include <ESP32_blelib.hh>

void ESP32_blelib::init(BLECharacteristic *pCharacteristicTX, BLECharacteristic *pCharacteristicRX)
{
    Serial.println("inside blelib init");
    deviceConnected = false;
    messageReceivedComplete = false;

    BLEDevice::init("ESP32BLE");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x1700));

    pServer->setCallbacks(new EchoServerCallbacks());
    pService->addCharacteristic(pCharacteristicTX);
    pService->addCharacteristic(pCharacteristicRX);

    pCharacteristicRX->addDescriptor(new BLE2902());
    pCharacteristicRX->setCallbacks(new ServerReadCallbacks());
    pCharacteristicRX->setValue("essa");
    pCharacteristicTX->addDescriptor(new BLE2902());

    pServer->getAdvertising()->addServiceUUID(serviceID);
    pService->start();
    pServer->getAdvertising()->start();
    Serial.println("Waiting for a Client to connect...");
}

// void BLEsetup(BLECharacteristic *pCharacteristicTX, BLECharacteristic *pCharacteristicRX)
// {
//     deviceConnected = false;
//     messageReceivedComplete = false;
//     BLEDevice::init("ESP32BLE");
//     BLEServer *pServer = BLEDevice::createServer();
//     // pServer->setCallbacks(new EchoServerCallbacks());
//     BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x1700));
//     pServer->setCallbacks(new EchoServerCallbacks());
//     // BLEService *pService = pServer->createService(BLEUUID((uint16_t)0x1700)); //  A random ID has been selected
//     pService->addCharacteristic(pCharacteristicTX);
//     pService->addCharacteristic(pCharacteristicRX);

//     pCharacteristicRX->addDescriptor(new BLE2902());
//     pCharacteristicRX->setCallbacks(new ServerReadCallbacks());
//     pCharacteristicRX->setValue("essa");
//     pCharacteristicTX->addDescriptor(new BLE2902());

//     pServer->getAdvertising()->addServiceUUID(serviceID);

//     // Start the service
//     pService->start();
//     // Start the Server/Advertising
//     pServer->getAdvertising()->start();

//     Serial.println("Waiting for a Client to connect...");
// }

// ESP32_blelib::ESP32_blelib()
// {

//     // Create and name the BLE Device
//     BLEDevice::init("ESP32BLE");

//     /* Create the BLE Server */
//     BLEServer *MyServer = BLEDevice::createServer();
//     MyServer->setCallbacks(new ServerCallbacks());  // Set the function that handles Server Callbacks

//     /* Add a service to our server */
//     BLEService *customService = MyServer->createService(BLEUUID((uint16_t)0x1700)); //  A random ID has been selected

//     /* Add a characteristic to the service */
//     customService->addCharacteristic(&customCharacteristic);  //customCharacteristic was defined above

//     /* Add Descriptors to the Characteristic*/
//     customCharacteristic.addDescriptor(new BLE2902());  //Add this line only if the characteristic has the Notify property

//     BLEDescriptor VariableDescriptor(BLEUUID((uint16_t)0x2901));  /*```````````````````````````````````````````````````````````````*/
//     VariableDescriptor.setValue("Temperature -40-60°C");          /* Use this format to add a hint for the user. This is optional. */
//     customCharacteristic.addDescriptor(&VariableDescriptor);    /*```````````````````````````````````````````````````````````````*/

//     /* Configure Advertising with the Services to be advertised */
//     MyServer->getAdvertising()->addServiceUUID(serviceID);

//     // Start the service
//     customService->start();

//     // Start the Server/Advertising
//     MyServer->getAdvertising()->start();

//     Serial.println("Waiting for a Client to connect...");
// }
