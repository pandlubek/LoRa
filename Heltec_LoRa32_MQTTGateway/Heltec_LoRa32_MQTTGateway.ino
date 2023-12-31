// external libraries
// https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series/releases/tag/0.0.8
#include "LoRaWan_APP.h"
#include "Arduino.h"
#include "WiFi.h"
#include "mbedtls/aes.h"
#include "Preferences.h"
#include "Wire.h"
#include "HT_SSD1306Wire.h"
// https://github.com/knolleary/pubsubclient
#include "PubSubClient.h"

// variables
unsigned long now = millis();
unsigned char * encryptedInputMessage;

// project files
#include "files/configuration.h"
#include "files/logo.h"
#include "files/display.h"
#include "files/wifi.h"
#include "files/aes.h"
#include "files/lora.h"
#include "files/lora_message.h"
#include "files/mqtt.h"
#include "files/mqtt_message.h"

void setup() 
{
  Serial.begin(115200);
  Mcu.begin();
  txNumber=0;
  rssi=0;

  initializeDisplay();
  delay(1000);

  initializeLoRaRadio();
  displayLoRaInfo();
  delay(3000);

  setupWiFi();
  displayWiFiInfo();
  delay(3000);

  mqttClient.setKeepAlive(MQTT_KEEP_ALIVE_TIME_IN_SEC);
  mqttClient.setCallback(mqttCallback);

  lora_idle = false;
  Serial.println("LoRa radio is listening (RX mode)...");
  Radio.Rx(0);
}

void loop()
{
  // current time
  now = millis();

  if (WiFi.status() != WL_CONNECTED)
  {
    setupWiFi();
    displayWiFiInfo();
    // TODO: If Wi-Fi or MQTT are not connected
    //       the last LoRa message should be saved in buffer 
    //       and send later
  }

  mqttConnection();

  publishMQTTMessage_Gateway_CpuTemp();

  // receive and decode LoRa message
  if(lora_idle)
  {
    encryptedInputMessage = reinterpret_cast<unsigned char *>(rxpacket);
    
    cleanEncryptedOutputMessage();
    cleanDecryptedOutputMessage();
    decrypt16(encryptedInputMessage, AES_KEY, decryptedOutputMessage);
    displayDecryptedOutputMessage();
    
    if (validateLoRaMessage())
    {
      updateLastSavedLoRaMessageNumber();
      publishMQTTMessage_Node_ContactSensor();
      publishMQTTMessage_Node_BatteryLevel();
    }

    lora_idle = false;
    Serial.println("LoRa radio is listening (RX mode)...");
    Radio.Rx(0);
  }
  Radio.IrqProcess();

  putTheDisplayToSleep();
}
