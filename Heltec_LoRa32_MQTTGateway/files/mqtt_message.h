void publishMQTTMessage_Node_ContactSensor()
{
  String topic = MQTT_NODE_TOPIC_PREFIX + extractLoRaIncomingMessageNodeId() + MQTT_TOPIC_CONTACT;
  String message = extractLoRaIncomingMessageContactSensorStatus();

  mqttClient.publish(topic.c_str(), message.c_str());

  Serial.printf("MQTT message has been published (topic: %s, value: %s)\r\n", topic.c_str(), message.c_str());
  
  oled.clear();
  oled.drawString(0, 0, "MQTT published:");
  oled.drawString(0, 10, topic);
  oled.drawString(0, 20, message);
  oled.display();
  rescheduleDisplaySleep();
}

void publishMQTTMessage_Node_BatteryLevel()
{
  String topic = MQTT_NODE_TOPIC_PREFIX + extractLoRaIncomingMessageNodeId() + MQTT_TOPIC_BATTERY;
  String message = String(extractLoRaIncomingMessageBatteryLevel());

  mqttClient.publish(topic.c_str(), message.c_str());

  Serial.printf("MQTT message has been published (topic: %s, value: %s)\r\n", topic.c_str(), message.c_str());
  
  oled.drawString(0, 30, topic);
  oled.drawString(0, 40, message);
  oled.display();
  rescheduleDisplaySleep();
}

unsigned long lastCpuTempReadTrigger = 0;
const int cpuTempReadIntervalInMiliseconds = CPU_TEMP_READ_INTERVAL_IN_SEC * 1000;
// source: https://www.theengineeringprojects.com/2022/01/esp32-internal-temperature-sensor.html
#ifdef __cplusplus
  extern "C" {
  #endif
  uint8_t temprature_sens_read();
  #ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

void publishMQTTMessage_Gateway_CpuTemp()
{
  if (now - lastCpuTempReadTrigger > cpuTempReadIntervalInMiliseconds)
  {
	String tempCelsius = String((temprature_sens_read() - 32) / 1.8);
    mqttClient.publish(MQTT_TOPIC_CPU_TEMP_CELSIUS, tempCelsius.c_str());
    Serial.printf("MQTT message has been published (topic: %s, value: %s)\r\n", MQTT_TOPIC_CPU_TEMP_CELSIUS, tempCelsius.c_str());

    String tempFahrenheit = String(temprature_sens_read());
    mqttClient.publish(MQTT_TOPIC_CPU_TEMP_FAHRENHEIT, tempFahrenheit.c_str());
    Serial.printf("MQTT message has been published (topic: %s, value: %s)\r\n", MQTT_TOPIC_CPU_TEMP_FAHRENHEIT, tempFahrenheit.c_str());
    
    lastCpuTempReadTrigger = millis();

    oled.clear();
    oled.drawString(0, 0, "MQTT published:");
    oled.drawString(0, 10, String(MQTT_TOPIC_CPU_TEMP_CELSIUS));
    oled.drawString(0, 20, tempCelsius);
	oled.drawString(0, 30, String(MQTT_TOPIC_CPU_TEMP_FAHRENHEIT));
    oled.drawString(0, 40, tempFahrenheit);
    oled.display();
	rescheduleDisplaySleep();
  }
}