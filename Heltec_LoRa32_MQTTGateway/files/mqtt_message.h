void publishMQTTMessage_ContactSensor()
{
	String topic = MQTT_NODE_TOPIC_PREFIX + extractLoRaIncomingMessageNodeId() + MQTT_TOPIC_CONTACT;
	String message = extractLoRaIncomingMessageContactSensorStatus();
	
	mqttClient.publish(topic.c_str(), message.c_str());
	
	Serial.printf("MQTT message has been published (topic: %s, value: %s)\r\n", topic.c_str(), message.c_str());
}

void publishMQTTMessage_BatteryLevel()
{
	String topic = MQTT_NODE_TOPIC_PREFIX + extractLoRaIncomingMessageNodeId() + MQTT_TOPIC_BATTERY;
	String message = String(extractLoRaIncomingMessageBatteryLevel());
	
	mqttClient.publish(topic.c_str(), message.c_str());
	
	Serial.printf("MQTT message has been published (topic: %s, value: %s)\r\n", topic.c_str(), message.c_str());
}

