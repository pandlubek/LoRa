Preferences preferences;
char decryptedInputMessage[16];
char batteryLevel[3];
char messageNumber[8];

void generateMessageNumber()
{
  preferences.begin("message", false);
  unsigned int counter = preferences.getUInt("counter", 0);
  counter++;
  preferences.putUInt("counter", counter);
  preferences.end();

  sprintf(messageNumber, "%08d", counter);
}

void resetMessageCounter()
{
  // TODO
  // 1/C/099/RRRRRRRR
}

void setBatteryLevel()
{  String lvl = getBatteryLevel();
  batteryLevel[0] = lvl[0];
  batteryLevel[1] = lvl[1];
  batteryLevel[2] = lvl[2];
}

void cleanDecryptedInputMessage()
{
  for (int i = 0; i < 16; i++)
  {
    decryptedInputMessage[i] = NULL;
  }
}

void createDecryptedInputMessage()
{
  decryptedInputMessage[0] = NODE_ID;
  decryptedInputMessage[1] = '/';
  //
  decryptedInputMessage[2] = getContactSensorStatus(true);
  decryptedInputMessage[3] = '/';
  //
  setBatteryLevel();
  decryptedInputMessage[4] = batteryLevel[0];
  decryptedInputMessage[5] = batteryLevel[1];
  decryptedInputMessage[6] = batteryLevel[2];
  decryptedInputMessage[7] = '/';
  //
  generateMessageNumber();
  decryptedInputMessage[8] = messageNumber[0];
  decryptedInputMessage[9] = messageNumber[1];
  decryptedInputMessage[10] = messageNumber[2];
  decryptedInputMessage[11] = messageNumber[3];
  decryptedInputMessage[12] = messageNumber[4];
  decryptedInputMessage[13] = messageNumber[5];
  decryptedInputMessage[14] = messageNumber[6];
  decryptedInputMessage[15] = messageNumber[7];
}

void displayDecryptedInputMessage()
{
  Serial.print("LoRa message: ");
  for (int i = 0; i < 16; i++)
  {
    Serial.print((char)decryptedInputMessage[i]);
  }
}

void sendLoRaMessage()
{
  cleanDecryptedInputMessage();
  createDecryptedInputMessage();
  displayDecryptedInputMessage();
        
  cleanEncryptedOutputMessage();
  encrypt16(decryptedInputMessage, AES_KEY, encryptedOutputMessage);

  for (int i = 0; i < 16; i++)
  {
    txpacket[i] = encryptedOutputMessage[i];
  }
  Serial.printf("\r\nSending packet \"%s\", length %d\r\n", txpacket, strlen(txpacket));
  Radio.Send( (uint8_t *)txpacket, strlen(txpacket) );
  delay(500);
}