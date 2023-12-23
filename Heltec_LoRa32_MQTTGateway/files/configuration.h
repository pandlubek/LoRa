
// Wi-Fi
#define WIFI_SSID     "your Wi-Fi name"
#define WIFI_PASSWORD "your Wi-Fi password"

// AES
#define AES_KEY "abcdefghijklmnop" // exactly 16 characters

// LoRa
#define RF_FREQUENCY                868000000 // Hz
#define TX_OUTPUT_POWER             14 // dBm
#define LORA_BANDWIDTH              0 // [0: 125 kHz, 1: 250 kHz, 2: 500 kHz, 3: Reserved]
#define LORA_SPREADING_FACTOR       9 // [SF7..SF12]
#define LORA_CODINGRATE             1 // [1: 4/5, 2: 4/6, 3: 4/7, 4: 4/8]
#define LORA_PREAMBLE_LENGTH        8 // Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT         0 // Symbols
#define LORA_FIX_LENGTH_PAYLOAD_ON  false
#define LORA_IQ_INVERSION_ON        false
#define RX_TIMEOUT_VALUE            1000
#define BUFFER_SIZE                 128 // Define the payload size here

// MQTT
#define MQTT_SERVER                    "XXX.XXX.XXX.XXX" // IP of the MQTT broker
#define MQTT_PORT                      1883
#define MQTT_CLIENT_ID                 "Heltec-LoRa32-MQTTGateway"
#define MQTT_ANONYMOUS_USER            true // set to false if you want to authenticate with username and password
#define MQTT_USERNAME                  "mqtt username here" // username
#define MQTT_PASSWORD                  "mqtt password here" // password in plain text
//
#define MQTT_NODE_TOPIC_PREFIX         "loragateway/node/"
//
#define MQTT_TOPIC_CONTACT             "/contactsensor" // publish contact sensor status
#define MQTT_MSG_CONTACT_OPEN          "OPEN"
#define MQTT_MSG_CONTACT_CLOSED        "CLOSED"
//
#define MQTT_TOPIC_BATTERY             "/batterylevel"
//
#define MQTT_TOPIC_LWT                 "loragateway/lwt" // LWT - availability of the LoRa gateway
#define MQTT_MSG_LWT_ONLINE            "ON" // message that is published to LWT channel when device is online
#define MQTT_MSG_LWT_OFFLINE           "OFF" // message that is published to LWT channel when device is offline
//
#define MQTT_KEEP_ALIVE_TIME_IN_SEC    60
#define MQTT_LWT_PING_INTERVAL_IN_SEC  300
