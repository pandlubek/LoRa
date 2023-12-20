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
- Replace the `configuration.h` file with a website where the user will be able to configure the required gateway parameters.

# Door sensor

## Basic information

This sketch is intended to be installed on Heltec LoRa3 [V3](https://resource.heltec.cn/download/WiFi_LoRa_32_V3/) board. Theoretically, it can be installed on the V2 or even V1 board with some modifications in the `configuration.h` file, but I do not recommend doing this, because the door sensor is to be battery-powered and the V3 board has the lowest power consumption in this mode (V2 800uA, V3 <10uA).

## Circuit diagram

![Circuit diagram](https://github.com/pandlubek/LoRa/assets/152999857/98bc71d2-c74e-4d84-8ae1-27341704bdf9)

An NC (normally open) or NC (normally closed) reed switch can be used. The switch type can be set in the `configuration.h` file.

## Electronic housing

Coming soon...

## Plans for the future

- Add support for remote configuration
- Create an extended version of this device with a built-in alarm siren
