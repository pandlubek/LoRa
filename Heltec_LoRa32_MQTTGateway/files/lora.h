char txpacket[BUFFER_SIZE];
char rxpacket[BUFFER_SIZE];
static RadioEvents_t RadioEvents;
int16_t txNumber;
int16_t rssi,rxSize;
bool lora_idle = true;

void OnRxDone(uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr)
{
  rssi=rssi;
  rxSize=size;
  memcpy(rxpacket, payload, size);
  rxpacket[size]='\0';
  Radio.Sleep( );
  
  Serial.printf("\r\nReceived packet: \"%s\", rssi: %d, length: %d", rxpacket, rssi, rxSize);
  
  oled.clear();
  oled.drawString(0, 0, "Received LoRa packet:");
  oled.drawString(0, 10, "Rssi: " + String(rssi) + ", length: " + String(rxSize));
  oled.display();

  lora_idle = true;
}

void initializeLoRaRadio()
{
  RadioEvents.RxDone = OnRxDone;
  Radio.Init(&RadioEvents);
  Radio.SetChannel(RF_FREQUENCY);
  Radio.SetRxConfig
  (
    MODEM_LORA, 
    LORA_BANDWIDTH, 
    LORA_SPREADING_FACTOR,
    LORA_CODINGRATE, 
    0, 
    LORA_PREAMBLE_LENGTH,
    LORA_SYMBOL_TIMEOUT, 
    LORA_FIX_LENGTH_PAYLOAD_ON,
    0, 
    true, 
    0, 
    0, 
    LORA_IQ_INVERSION_ON, 
    true 
  );
}

void displayLoRaInfo()
{
  oled.clear();
  oled.drawString(0, 0, "LoRa radio initialized");
  oled.drawString(0, 10, "Frequency: " + String(RF_FREQUENCY));
  
  switch(LORA_BANDWIDTH)
  {
    case 0:
      oled.drawString(0, 20, "Bandwidth: 125 kHz");
      break;
    case 1:
      oled.drawString(0, 20, "Bandwidth: 250 kHz");
      break;
    case 2:
      oled.drawString(0, 20, "Bandwidth: 500 kHz");
      break;
    default:
      oled.drawString(0, 20, "Bandwidth: undefined!");
      break;
  }
  
  oled.drawString(0, 30, "Spreading factor: " + String(LORA_SPREADING_FACTOR));
  oled.drawString(0, 40, "Preamble length: " + String(LORA_PREAMBLE_LENGTH));
  oled.display();
}
