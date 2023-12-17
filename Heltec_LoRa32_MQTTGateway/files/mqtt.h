bool mqttMotionMessagePublished = false;
unsigned long lastMotionTrigger = 0;
unsigned long lastMQTTConnectionTrigger = 0;
unsigned long lastMQTTPingTrigger = 0;
const int mqttLWTPingIntervalInMilliseconds = MQTT_LWT_PING_INTERVAL_IN_SEC * 1000;
WiFiClient wifiClient;
PubSubClient mqttClient(MQTT_SERVER, MQTT_PORT, wifiClient);

void mqttCallback(char* topic, byte* message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // handling incomming mesages
  // not implemented yet
}

void mqttConnection()
{
  // break if Wi-Fi not connected
  // or last connection attempt was earlier then 5 seconds ago
  if (WiFi.status() != WL_CONNECTED ||
     (now - lastMQTTConnectionTrigger) < 5000)
  {
    return;
  }

  // loop and break if MQTT already connected
  if (mqttClient.connected())
  {
    // send LWT online message every 60 secods
    if ((now - lastMQTTPingTrigger) > mqttLWTPingIntervalInMilliseconds)
    {
      mqttClient.publish(MQTT_TOPIC_LWT, MQTT_MSG_LWT_ONLINE);
      lastMQTTPingTrigger = millis();
    }
    mqttClient.loop();
    return;
  }

  // try to connect to MQTT every 5 seconds
  Serial.print("Attempting MQTT connection...");
  if ((MQTT_ANONYMOUS_USER && mqttClient.connect(MQTT_CLIENT_ID, MQTT_TOPIC_LWT, 1, false, MQTT_MSG_LWT_OFFLINE)) ||
    (!MQTT_ANONYMOUS_USER &&  mqttClient.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD, MQTT_TOPIC_LWT, 1, false, MQTT_MSG_LWT_OFFLINE)))
  {
    Serial.println(" connected");
    mqttClient.publish(MQTT_TOPIC_LWT, MQTT_MSG_LWT_ONLINE);
    lastMQTTPingTrigger = millis();
	Serial.printf("MQTT LWT topic: %s\r\n", MQTT_TOPIC_LWT);
    // Subscribe channels
    //mqttClient.subscribe("MQTT channel here");
  }
  else
  {
    Serial.print(" failed, rc=");
    Serial.print(mqttClient.state());
  }
  lastMQTTConnectionTrigger = millis();
}