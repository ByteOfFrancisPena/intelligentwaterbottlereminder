# intelligentwaterbottlereminder
Device to track water levels in a bottle and send notifications if it has not been drank in a while

[Image Download.zip](https://github.com/user-attachments/files/27033814/Image.Download.zip)
<img width="1026" height="1824" alt="image1" src="https://github.com/user-attachments/assets/aba5cfea-d24f-456f-b71a-47528c950b16" />

Requirements:
* Arduino Software
* Telegram (for notifications)
* ESP32
* Jumper wires
* Copper Tape
* Bottle (non-metal)

Libraries Needed:
* UniversalTelegramBot
* ArduinoJson

Steps:
* Cut 2 pieces of copper and place them to your bottle vertically and on opposing sides
* Install sketch and adjust your credentials. Use @BotFather and @userinfobot on Telegram to make a bot to notify you and to get you Telegram ID respectively
* Compile then program the sketch into your ESP32
* Connect one copper piece to Pin 15 of your ESP32, and the other copper piece to ground
* Plug the device to power and it should work
