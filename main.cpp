/*#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "Arduino.h"
#include <math.h>

#define SERVICE_UUID        "fb91008e-0499-4684-b266-caabfaaef7a1"
#define CHARACTERISTIC_UUID "078659d5-eee7-41ec-8739-c58f8b967393"

void setup() {
  Serial.begin(9600);

  BLEDevice::init("ESP32");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);

  pService->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x12);
  pAdvertising->setMaxInterval(10);
  pAdvertising->setMinInterval(1000);
  pAdvertising->start();
}

void loop() {
    int N = 2;
    int transmit_power = -69;
    BLEScan *newScan = BLEDevice::getScan(); 
    newScan->start(5, false);
    BLEScanResults results = newScan->getResults();

    for (int i = 0; i < results.getCount(); i++)
    {

        Serial.print(pow(10, (transmit_power - results.getDevice(i).getRSSI())/(10 * N)));
        Serial.print("\n");
    }

    
    newScan->clearResults();
}*/
//#define _GLIBCXX_USE_CXX11_ABI 0
/*#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <Arduino.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

void setup() {
  Serial.begin(9600);

  BLEDevice::init("esp32 bate");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);
  //pAdvertising->setMinPreferred(0x12);
  pAdvertising->start();

  //pinMode(0, OUTPUT);
  //pinMode(2, OUTPUT);
  //pinMode(4, OUTPUT);
}

void loop() {
  int N = 2;
  int transmit_power = -66;
  BLEScan *newScan = BLEDevice::getScan(); 
  newScan->setActiveScan(true);
  newScan->setWindow(100);
  newScan->start(2, false);
  BLEScanResults results = newScan->getResults();


  for (int i = 0; i < results.getCount(); i++)
  {

      Serial.print(pow(10, (transmit_power - results.getDevice(i).getRSSI())/(10 * N)));
      /*if(results.getDevice(i).getRSSI() < 0)
      {
        if(results.getCount() > 0)
        {
          Serial.println("eho");
        }
        else
        {
          Serial.println("ehooooooo");
        }
      }
  }


  newScan->clearResults();
}*/
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEScan.h>
#include "BLEBeacon.h"

BLEAdvertising *pAdvertising;
#define BEACON_UUID "8ec76ea3-6668-48da-9866-75be8bc86f4d"
void setBeacon() {

  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(0x4C00);
  oBeacon.setProximityUUID(BLEUUID(BEACON_UUID));
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();
  
  oAdvertisementData.setFlags(0x12);
  
  std::string strServiceData = "";
  
  std::string str1(1, (char)26);
  std::string str2(1, (char)0xFF);

  strServiceData.append(str1);
  strServiceData.append(str2);
  strServiceData.append(oBeacon.getData()); 
  oAdvertisementData.addData(strServiceData);
  
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);
  pAdvertising->setMinInterval(100);

}

void setup() {

    
  Serial.begin(9600);
  
  BLEDevice::init("esp 32 bate");

  pAdvertising = BLEDevice::getAdvertising();
  
  setBeacon();
  pAdvertising->start();

  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(4, OUTPUT);

}
void loop() {
  const int N = 2;
  int transmit_power = -69;
  BLEScan *newScan = BLEDevice::getScan(); 
  newScan->setActiveScan(true);
  newScan->setWindow(100);
  newScan->start(2, false);
  BLEScanResults results = newScan->getResults();


  for (int i = 0; i < results.getCount(); i++)
  {
      if(strcmp(results.getDevice(i).getName().c_str(), "Xiaomi Watch S1 C457") == 0)
      {
          double exponent = ((double)(transmit_power - results.getDevice(i).getRSSI())) / (double)(10 * N), number = 10;
          if(pow(number, exponent) < 2.0)
          {
              digitalWrite(27, HIGH);
              digitalWrite(26, LOW);
              digitalWrite(25, LOW);
              digitalWrite(4, LOW);
          }
          else if(pow(number, exponent) < 4.0)
          {
              digitalWrite(27, LOW);
              digitalWrite(26, HIGH);
              digitalWrite(25, LOW);
              digitalWrite(4, LOW);
          }
          else
          {
              digitalWrite(27, LOW);
              digitalWrite(26, LOW);
              digitalWrite(25, HIGH);
              digitalWrite(4, HIGH);
          }
      }
  }


  newScan->clearResults();
}