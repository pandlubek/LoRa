// external libraries
#include "LoRaWan_APP.h"
#include "Arduino.h"
#include "mbedtls/aes.h"
#include "Preferences.h"
#include "driver/rtc_io.h"

// variables
bool messagePublished = false;
unsigned long now = millis();
unsigned long lastAwakening = 0;

// project files
#include "files/configuration.h"
#include "files/contactsensor.h"
#include "files/battery.h"
#include "files/aes.h"
#include "files/lora.h"
#include "files/lora_message.h"
#include "files/deepsleep.h"

void setup()
{
  rtc_gpio_deinit((gpio_num_t)CONTACT_SENSOR_GPIO_NUM);
  
  Serial.begin(115200);
  Mcu.begin();
  
  initializeLoRaRadio();
  
  Serial.println();
  print_wakeup_reason();
  rtc_gpio_pulldown_en((gpio_num_t)CONTACT_SENSOR_GPIO_NUM);
  esp_sleep_enable_ext0_wakeup((gpio_num_t)CONTACT_SENSOR_GPIO_NUM, CONTACT_SENSOR_TYPE); //1 = High, 0 = Low
  esp_sleep_enable_timer_wakeup(WAKEUP_INTERVAL_IN_SEC * 1000000);
  Serial.printf("Setup Heltec board to sleep for every %d (%dm or %dh)\r\n", WAKEUP_INTERVAL_IN_SEC, WAKEUP_INTERVAL_IN_SEC/60, WAKEUP_INTERVAL_IN_SEC/3600);
}

void loop()
{
  now = millis();

  char contactSensorStatus = getContactSensorStatus();

  if (contactSensorStatus == CONTACT_SENSOR_STATUS_OPEN)
  {
    if (!messagePublished || (now - lastAwakening > WAKEUP_INTERVAL_IN_SEC * 1000))
    {
      if(lora_idle == true)
      {
        sendLoRaMessage();
        lora_idle = false;
        messagePublished = true;
        lastAwakening = millis();
      }
      Radio.IrqProcess();

      readBatteryVoltage(true);
      Serial.println();
    }
  }
  else
  {
    if(lora_idle == true)
    {
      sendLoRaMessage();
      lora_idle = false;
      messagePublished = false;
      lastAwakening = millis();
    }
    Radio.IrqProcess();

    readBatteryVoltage(true);
    
    Serial.printf("Going to sleep now for %ds (%dm or %dh)\r\n", WAKEUP_INTERVAL_IN_SEC, WAKEUP_INTERVAL_IN_SEC/60, WAKEUP_INTERVAL_IN_SEC/3600);
    esp_deep_sleep_start();

    Serial.println();
  }
}
