# SmartWatering
## A smart autonomous system for watering plants and tracking the environment with the ability to take photos, besides sending it in a telegram bot
---
### System works on
* Arduino Uno + Troyka Shield
* Raspberry Pi 3 Model B+
### Dependencies
#### Arduino
* [QuadDisplay](https://github.com/amperka/QuadDisplay2)
* [TroykaLight](https://www.arduino.cc/reference/en/libraries/troykalight/)
* [TroykaDHT](https://github.com/amperka/TroykaDHT)
* [ArduinoJson](https://www.arduino.cc/reference/en/libraries/arduinojson/)
#### Raspberry Pi
* [pyserial](https://pypi.org/project/pyserial/)
* [aiogram](https://pypi.org/project/aiogram/)
* [picamera](https://pypi.org/project/picamera/)
### Modules
#### Arduino
* [Button](https://amperka.ru/product/troyka-button)
* [DHT](https://amperka.ru/product/troyka-temperature-humidity-sensor-dht11)
* [Humidity](https://amperka.ru/product/soil-moisture-sensor)
* [Light](https://amperka.ru/product/troyka-light-sensor)
* [Led](https://amperka.ru/product/troyka-led-module)
* [Pump](https://amperka.ru/product/immersible-water-pump)
* [Indicator](https://amperka.ru/product/troyka-quad-display)
#### Raspberry Pi
* [Camera](https://amperka.ru/product/raspberry-pi-camera-board-v2)
### Launch
* Сonnecting all modules
* Downloading libraries and firmware to Arduino
* Connect the Arduino to Raspberry Pi
* Connecting to Raspberry Pi via ssh
* Installing the necessary libraries
* Uploading Python the file
* Run in the background via nohup
* Done
> In the process of connecting modules, downloading libraries, downloading firmware, establishing a connection, etc., you may have difficulties\
> Good luck
