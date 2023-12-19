# LoRa to MQTT Gateway

## Basic information

This sketch is intended to be installed on Heltec LoRa32 board ([V2](https://resource.heltec.cn/download/WiFi_LoRa_32/V2.1) or [V3](https://resource.heltec.cn/download/WiFi_LoRa_32_V3/)).
There's a chance it will work fine on the V1 board as well, but I haven't had a chance to test this setup.

The main goal of this sketch is to receive LoRa messages from connected nodes, translate them into MQTT messages and publish them to the MQTT broker.
Communication between gateway and nodes is encrypted using the **AES-128** algorithm.

All configuration parameters are located in the `configuration.h` file.

## Electronic housing

If you are interested in a case for this device, you can print it using this [3D model](https://www.thingiverse.com/thing:6363352).

![Electronic housing](https://cdn.thingiverse.com/assets/9e/2d/06/bb/97/large_display_609d20ab-3c6b-4e26-bdd4-fccceb8b7cda.jpg)

## Plans for the future
- Add support for built-in OLED display
- Replace the configuration.h file with a website where the user will be able to configure the required gateway parameters.

# Door sensor

// TODO
