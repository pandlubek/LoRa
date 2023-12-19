// message
// - format: noodeId/sensorStatus/batteryLevel/messageNumber
// - example: 1/C/100/99999999
// - nodeId: 1-9, exactly 1 digit
// - sensorStatus: O - open, C - closed, exactly 1 char
// - batteryLevel: 000-100, exactly 3 digits
// - messageCounter: max 99999999, incremented by 1, exactly 8 digits
#define NODE_ID                       '1' // 1-9
#define CONTACT_SENSOR_STATUS_CLOSED  'C'
#define CONTACT_SENSOR_STATUS_OPEN    'O'
#define AES_KEY                       "abcdefghijklmnop" // exactly 16 characters

// LoRa
#define RF_FREQUENCY                868000000 // Hz
#define TX_OUTPUT_POWER             5 // dBm
#define LORA_BANDWIDTH              0 // [0: 125 kHz, 1: 250 kHz, 2: 500 kHz, 3: Reserved]
#define LORA_SPREADING_FACTOR       7 // [SF7..SF12]
#define LORA_CODINGRATE             1 // [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
#define LORA_PREAMBLE_LENGTH        8 // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT         0 // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON  false
#define LORA_IQ_INVERSION_ON        false
#define RX_TIMEOUT_VALUE            1000
#define BUFFER_SIZE                 128 // Define the payload size here

// deep sleep mode
#define WAKEUP_INTERVAL_IN_SEC      60 // 86400 24h

// contact sensor
#define CONTACT_SENSOR_TYPE         1 // 1 - NO (normally open), 0 - NC (normally closed)
#define CONTACT_SENSOR_GPIO_NUM     0