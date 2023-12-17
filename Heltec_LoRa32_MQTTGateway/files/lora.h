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
