/**
 * A BLE client example that is rich in capabilities.
 */

#include "BLEDevice.h"
//#include "BLEScan.h"
#include <iostream>
#include <iterator>
using namespace std;

#include "esp_log.h"


// bulb id: a4:c1:38:b7:12:d8
// The remote service we wish to connect to.
static BLEUUID serviceUUID("0000cdab-0000-1000-8000-00805f9b34fb"); // a LED lightbulb like were looking for. comes from the device itself, before connecting
static BLEUUID svcWithCharacteristics("00010203-0405-0607-0809-0a0b0c0d1910"); // this is the one with characteristics
// -> [D][BLEClient.cpp:358] getServices(): >> getServices
//           srvc_id: uuid: 00001800-0000-1000-8000-00805f9b34fb
//           srvc_id: uuid: 0000180a-0000-1000-8000-00805f9b34fb
//           srvc_id: uuid: 00010203-0405-0607-0809-0a0b0c0d1910 <-- this is the one with characteristics



// The characteristic of the remote service we are interested in.
static BLEUUID    charUUID("0d563a58-196a-48ce-ace2-dfec78acc814");

static BLEAddress *pServerAddress;
static boolean doConnect = false;
static boolean connected = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;

static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
    Serial.print("Notify callback for characteristic ");
    Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print(" of data length ");
    Serial.println(length);
}

bool connectToServer(BLEAddress pAddress) {
    Serial.print("Forming a connection to ");
    Serial.println(pAddress.toString().c_str());
    
    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    // Connect to the remove BLE Server.
    pClient->connect(pAddress);
    Serial.println(" - Connected to server");

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(svcWithCharacteristics);
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(svcWithCharacteristics.toString().c_str());
      return false;
    }
    Serial.println(" - Found our service");
    Serial.println(pRemoteService->toString().c_str());
    Serial.println("---");

    Serial.println("\n\n\HEREn\n");
    BLEUUID a("00010203-0405-0607-0809-0a0b0c0d1911");
    BLEUUID b("00010203-0405-0607-0809-0a0b0c0d1912");
    BLEUUID c("00010203-0405-0607-0809-0a0b0c0d1913");
    BLEUUID d("00010203-0405-0607-0809-0a0b0c0d1914");
    Serial.printf("a: '%s'", pRemoteService->getCharacteristic(a)->readValue().c_str());
    Serial.printf("b: '%s'", pRemoteService->getCharacteristic(b)->readValue().c_str());
    Serial.printf("c: '%s'", pRemoteService->getCharacteristic(c)->readValue().c_str());
    Serial.printf("d: '%s'", pRemoteService->getCharacteristic(d)->readValue().c_str());
    Serial.println("-----");

    
    /*std::map<std::string, BLERemoteCharacteristic*>* characteristics = pRemoteService->getCharacteristics();
    for (std::map<std::string, BLERemoteCharacteristic*>::iterator it=characteristics->begin(); it!=characteristics->end(); ++it) {
      Serial.println(it->first.c_str());
      if(it->second->canRead()) {
        Serial.println(it->second->toString().c_str());
        Serial.print("'");
        Serial.print(it->second->readValue().c_str());
        Serial.println("'");
      } else {
        Serial.println("cant read it");
      }      
      Serial.println("----");
    }*/
    Serial.println("e");
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    Serial.println("f");
    if (pRemoteCharacteristic == nullptr) {
      Serial.println("g");
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
      pClient->disconnect(); // TODO necessary?
      return false;
    }
    Serial.println(" - Found our characteristic");

    // Read the value of the characteristic.
    std::string value = pRemoteCharacteristic->readValue();
    Serial.print("The characteristic value was: ");
    Serial.println(value.c_str());

    pRemoteCharacteristic->registerForNotify(notifyCallback);
}
/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
 /**
   * Called for each advertising BLE server.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());
//TODO check device address is in list
//bulb address: a4:c1:38:b7:12:d8 = getAddress().toString().c_str()
    // We have found a device, let us now see if it contains the service we are looking for.

    Serial.println(advertisedDevice.toString().c_str());
    
    Serial.println("a");
    Serial.println(advertisedDevice.haveServiceUUID());
    if(advertisedDevice.haveServiceUUID()) {
      Serial.println("b");
      Serial.println(advertisedDevice.getServiceUUID().toString().c_str());
      Serial.println("c");
      if (advertisedDevice.haveServiceUUID() && advertisedDevice.getServiceUUID().equals(serviceUUID)) {  
        //
        Serial.print("Found our device!  address: "); 
        advertisedDevice.getScan()->stop();
  
        pServerAddress = new BLEAddress(advertisedDevice.getAddress());
        doConnect = true;
Serial.println("d");
      } // Found our server
    }
    Serial.println("e");
  } // onResult
}; // MyAdvertisedDeviceCallbacks


void setup() {

  esp_log_level_set("*", ESP_LOG_INFO);

  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");
  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 30 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(15);
} // End of setup.


// This is the Arduino main loop function.
void loop() {

  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are 
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer(*pServerAddress)) {
      Serial.println("We are now connected to the BLE Server.");
      connected = true;
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    //doConnect = false;
  }

  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.
  if (connected) {
    //String newValue = "Time since boot: " + String(millis()/1000);
    //Serial.println("Setting new characteristic value to \"" + newValue + "\"");
    
    // Set the characteristic's value to be the array of bytes that is actually a string.
    //pRemoteCharacteristic->writeValue(newValue.c_str(), newValue.length());
  }
  
  delay(1000); // Delay a second between loops.
} // End of loop
