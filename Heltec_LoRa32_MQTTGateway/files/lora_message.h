int extractLoRaIncomingMessageNumber()
{
	char tmp[8] = 
	{
		decryptedOutputMessage[8],
		decryptedOutputMessage[9],
		decryptedOutputMessage[10],
		decryptedOutputMessage[11],
		decryptedOutputMessage[12],
		decryptedOutputMessage[13],
		decryptedOutputMessage[14],
		decryptedOutputMessage[15]
	};
	
	return atoi(tmp);
}

int extractLoRaIncomingMessageBatteryLevel()
{
	char tmp[3] = 
	{
		decryptedOutputMessage[4],
		decryptedOutputMessage[5],
		decryptedOutputMessage[6]
	};
	
	return atoi(tmp);
}

String extractLoRaIncomingMessageNodeId()
{
	return String((char)decryptedOutputMessage[0]);
}

String extractLoRaIncomingMessageContactSensorStatus()
{
	if ((char)decryptedOutputMessage[2] == 'C')
	{	
		return MQTT_MSG_CONTACT_CLOSED;
	}
	else if ((char)decryptedOutputMessage[2] == 'O')
	{
		return MQTT_MSG_CONTACT_OPEN;
	}
	else
	{
		return "NULL";
	}
}

Preferences preferences;

int getLastSavedLoRaMessageNumber()
{
	String counterName = "counter_node_" + extractLoRaIncomingMessageNodeId();
	preferences.begin("message", false);
	unsigned int counter = preferences.getUInt(counterName.c_str(), 0);
	preferences.end();
	
	return counter;
}

void updateLastSavedLoRaMessageNumber()
{
	int incomingMessageNumber = extractLoRaIncomingMessageNumber();
	String nodeId = extractLoRaIncomingMessageNodeId();
	String counterName = "counter_node_" + nodeId;
	preferences.begin("message", false);
	unsigned int counter = preferences.getUInt(counterName.c_str(), 0);
	
	preferences.putUInt(counterName.c_str(), incomingMessageNumber);
	Serial.printf("The message number for the node %s has been updated from %d to %d\r\n", nodeId, counter, incomingMessageNumber);
	
	preferences.end();
}

void removeLastSavedLoRaMessageNumber(int nodeId)
{
	String counterName = "counter_node_" + String(nodeId);
	preferences.begin("message", false);
	unsigned int counter = preferences.getUInt(counterName.c_str(), 0);
	
	preferences.remove(counterName.c_str());
	Serial.printf("Data saved for key %s has been deleted\r\n", counterName.c_str());
	
	preferences.end();
}

bool validateLoRaMessage()
{
  // message format
  // 1/C/100/99999999
  // 1 - node id
  // C - sensor status
  // 100 - battery level
  // 99999999 - message number that has to be larger than last previous one

  if (decryptedOutputMessage[1] != '/' ||
      decryptedOutputMessage[3] != '/' ||
      decryptedOutputMessage[7] != '/')
      {
        Serial.println("Invalid LoRa message");
        return false;
      }

  if (decryptedOutputMessage[2] != 'C' &&
      decryptedOutputMessage[2] != 'O')
      {
        Serial.println("Invalid LoRa message");
        return false;
      }

  if (!isdigit(decryptedOutputMessage[0]) ||
      !isdigit(decryptedOutputMessage[4]) ||
      !isdigit(decryptedOutputMessage[5]) ||
      !isdigit(decryptedOutputMessage[6]) ||
      !isdigit(decryptedOutputMessage[8]) ||
      !isdigit(decryptedOutputMessage[9]) ||
      !isdigit(decryptedOutputMessage[10]) ||
      !isdigit(decryptedOutputMessage[11]) ||
      !isdigit(decryptedOutputMessage[12]) ||
      !isdigit(decryptedOutputMessage[13]) ||
      !isdigit(decryptedOutputMessage[14]) ||
      !isdigit(decryptedOutputMessage[15]))
      {
        Serial.println("Invalid LoRa message");
        return false;
      }

  int incommingMessageNumber = extractLoRaIncomingMessageNumber();
  int savedMessageNumber = getLastSavedLoRaMessageNumber();
  if (incommingMessageNumber <= savedMessageNumber)
  {
    Serial.printf("LoRa message is valid, but the incomming message numer (%s) is lower than the last one saved (%s)\r\n", String(incommingMessageNumber), String(savedMessageNumber));
    return false;
  }

  Serial.println("LoRa message is valid");
  return true;
}
