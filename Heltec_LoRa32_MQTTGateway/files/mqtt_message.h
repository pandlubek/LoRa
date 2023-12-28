void publishMQTTMessage_Node_ContactSensor()
{
  String topic = MQTT_NODE_TOPIC_PREFIX + extractLoRaIncomingMessageNodeId() + MQTT_TOPIC_CONTACT;
  String message = extractLoRaIncomingMessageContactSensorStatus();

  mqttClient.publish(topic.c_str(), message.c_str());

  Serial.printf("MQTT message has been published (topic: %s, value: %s)\r\n", topic.c_str(), message.c_str());
}

void publishMQTTMessage_Node_BatteryLevel()
{
  String topic = MQTT_NODE_TOPIC_PREFIX + extractLoRaIncomingMessageNodeId() + MQTT_TOPIC_BATTERY;
  String message = String(extractLoRaIncomingMessageBatteryLevel());

  mqttClient.publish(topic.c_str(), message.c_str());

  Serial.printf("MQTT message has been published (topic: %s, value: %s)\r\n", topic.c_str(), message.c_str());
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
  }
}