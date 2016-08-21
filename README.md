# ESP8266_TelegramBot_Terminal
Basic Telegram Bot Terminal example implementation on the ESP8266 SOC

The program represent a Bot Terminal for see input/output data from the ESP8266 (just like Serial Terminal do), It implements read() and println() functions.

In this example, we send analog data read from A0 pin (AnalogRead Sketch).

Note: For initialice the bot communication  we need the ID bot, to get it the user need to send any message before the Terminal start to work (telegram_begin() function are blocking).

The next libraries are necessaries:
 - UniversalTelegramBot: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
 - ArduinoJson: Search it by Arduino IDE.
