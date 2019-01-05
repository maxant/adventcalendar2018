# what is this?

a playground for my shiny new arduino :-)

## copied stuff:

this isnt from me:

- *.bin => https://iot.fkainka.de/nodeesp
- nodeesp32_board.jpg => from fkainka.de or https://github.com/espressif/arduino-esp32

## To Read

https://docs.espressif.com/projects/esp-idf/en/latest/get-started/linux-setup.html
file:///home/ant/Downloads/Arduino%20In%20A%20Nutshell%201.13.pdf
https://github.com/FKainka/NanoESP/
https://www.heise.de/make/artikel/ESP-Boards-mit-der-Arduino-IDE-programmieren-4130861.html
https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/ => has some simple programs
https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
https://playground.arduino.cc/Main/ManualsAndCurriculum
http://fritzing.org/home/
??? https://arduino-esp8266.readthedocs.io/en/latest/libraries.html#mdns-and-dns-sd-responder-esp8266mdns-library

## References

https://iot.fkainka.de/nodeesp-command-reference
https://www.espressif.com/en/support/download/overview
https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf
https://iot.fkainka.de/driver => couldnt get it to compile
http://playground.arduino.cc/Learning/Linux => altho it seems you can just install it on ubuntu
https://www.arduino.cc/en/Guide/Troubleshooting#upload
http://playground.arduino.cc/Linux/All#Permission

button: doesnt work: https://forum.arduino.cc/index.php?topic=72276.0
        good: https://www.arduino.cc/en/Tutorial/InputPullupSerial

webserver: https://github.com/espressif/arduino-esp32/blob/master/libraries/WebServer/src/WebServer.cpp

pin map: https://github.com/espressif/arduino-esp32/

pin reference: https://randomnerdtutorials.com/esp32-pinout-reference-gpios/

lots of stuff can be included from here: /home/ant/.arduino15/packages/esp32/hardware/esp32/1.0.0/tools/sdk/include
 e.g. driver/driver/adc.h

## TODO

- https://www.espressif.com/sites/default/files/documentation/esp32_bluetooth_networking_user_guide_en.pdf
- Serial.setDebugOutput(true); => and how do eg BLE classes do their debug output to serial?
- https://randomnerdtutorials.com/rf-433mhz-transmitter-receiver-module-with-arduino/
- deep sleep
- OTA update
- use eeprom for config settings
- MQTT https://www.baldengineer.com/mqtt-tutorial.html
  - https://github.com/espressif/esp-mqtt
- lcd - can we tune it? can i use resistors to make it not need variable ones?
- Serial2.begin(9600, SERIAL_8N1, 16,17); // rx=16, tx=17
  - while(Serial2.available()) Serial.println(char(Serial2.read()));
  - 2:47 @ https://www.youtube.com/watch?v=eUPAoP7xC7A
- ILI9341: https://www.youtube.com/watch?v=cOH7vcLCKhE uses SPI
  - https://github.com/G6EJD/ESP32-and-how-to-use-ILI9341-TFT-Display
- MOSI = master out slave in
- multiple i2c: https://www.youtube.com/watch?v=QQLfzlPGjjE
- touch tft: https://ch.rs-online.com/web/p/entwicklungskits-grafikdisplay/7916378/
- gps: 
- lidar: https://www.youtube.com/watch?v=VhbFbxyOI1k
  - http://wiki.seeedstudio.com/Grove-TF_Mini_LiDAR/
  - RS Best.-Nr. 174-3264
- "RS Pro Tragbares Gehäuse ABS" => boxes
- fix error relating to wifi connect that seems to come when we make an http request
- reconnect if wifi lost? => works out-of-the-box
- https://www.arduino.cc/en/Reference/EEPROM

## ESP-IDF

https://docs.espressif.com/projects/esp-idf/en/latest/get-started

    export IDF_PATH=/w/adventcalendar2018/esp-idf

==========================================

PINS

dont use 6-11 => flash

r=4
g=2
b=0

SD => need to work out how to use serial bus

==========================================

http://nodeesp.local/

	cd /w/adventc...2018/
	node_modules/node-red/bin/node-red-pi

http://127.0.0.1:1880/

http://127.0.0.1:1880/ui/#/0

==========================================

## day 4

udp works

<any string> => {"cmd":"ack"}
{"cmd":"ping"} => {"cmd": "pong"}
{"cmd": "get_wifi_status"} => connection status
{"cmd": "get_wifi_scan"} detect and list all Wi-Fi networks in range


## day 5 node-red

node_modules/node-red/bin/node-red-pi
http://127.0.0.1:1880/


## day 6 node-red

## day 7 treppenlicht

set udp sending node to use address "nodeesp.local"
enable/disable flows by double clicking on their tab
use aruino port monitor after connecting to usb to check any messages from board
long LED pin connects to resistor. short leg to ground.

## day 8 ein regler

command reference from https://iot.fkainka.de/nodeesp-command-reference

    {"cmd":"get_button_config"}
    {"cmd":"get_button_state"}

## day 9 photo transistor

cathode is short leg, goes to positive, opposite of an LED! looks like a see thru led, with one side (short leg cathode) trimmed flat. long leg to gnd.

3.3v  -> pot left leg
gnd   -> pot right leg
wiper -> adc pin (36)
wiper -> short leg of photo transistor
ph.tr.long -> gnd

turn lights off. set pot so adc pin reads about 4000
turn lights on. adc pin now reads lower, the brighter it gets.

## day 10 deep sleep

the idea is to sleep the board and take a reading of sunlight only every say minute.

## day 11 MQTT

TODO

## day 15 IR receiver

black with a round bump and three pins

connects with middle leg to gnd. use pins 21 (wire sda) and 19 (v spi miso master in slave out). make bump face outwards away from esp32.

looking at bump, out is on right (21), v+ is on left (19).

http://www.circuitbasics.com/arduino-ir-remote-receiver-tutorial/

=> zip taken from: http://z3t0.github.io/Arduino-IRremote/ => not tried...

TODO do i need to remove sd card?

https://github.com/cyborg5/IRLib2/blob/master/IRLib2/manuals/IRLibReference.pdf => didnt compile

https://www.youtube.com/watch?v=gADIb1Xw8PE
=> https://github.com/SensorsIot/Definitive-Guide-to-IR/blob/master/IRMQTT_ESP32/IRMQTT_ESP32.ino => looks promising! should work on ESP32
=> => seems to take code from http://z3t0.github.io/Arduino-IRremote/ => installed zip as per instructions by unzipping and placing into libraries folder
=> => compatible with http://www.circuitbasics.com/arduino-ir-remote-receiver-tutorial/ ???

works!
looking at bump: left -> pin21, middle -> gnd, right -> 5v

IR LED: slightly bluish tint.
short leg of IR led to ground
long leg of IR led to pin 17


## BLE LED Bulb

22:40:06.717 -> Advertised Device: Name: unpaired, Address: a4:c1:38:b7:12:d8, manufacturer data: 60012910d812b738010204d8000364ff00000101000000000000000000, serviceUUID: 00001800-0000-1000-8000-00805f9b34fb 

22:40:06.841 -> Advertised Device: Name: ENVY Photo 6200 series, Address: 4a:ba:4e:6a:42:3d, manufacturer data: 650001c901, serviceUUID: 0000fe78-0000-1000-8000-00805f9b34fb, txPower: 6 

https://medium.com/@urish/reverse-engineering-a-bluetooth-lightbulb-56580fcb7546

https://www.arduino.cc/en/Reference/CurieBLE

record ble from app:

developer in android: https://www.google.com/search?q=huawei+p20+lite+android+6+developer+mode&oq=huawei+p20+lite+android+6+developer+mode&aqs=chrome..69i57.14761j1j7&sourceid=chrome&ie=UTF-8
click loads on settings->aboutPhone->buildNumber


ON::RED
1:28:36.696 -> [D][BLERemoteCharacteristic.cpp:434] readValue(): >> readValue(): uuid: 00010203-0405-0607-0809-0a0b0c0d1911, handle: 18 0x12
01:28:36.763 -> 1,;1
01:28:36.763 -> [D][BLERemoteCharacteristic.cpp:434] readValue(): >> readValue(): uuid: 00010203-0405-0607-0809-0a0b0c0d1912, handle: 21 0x15
01:28:36.829 -> 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,;16
01:28:36.829 -> [D][BLERemoteCharacteristic.cpp:434] readValue(): >> readValue(): uuid: 00010203-0405-0607-0809-0a0b0c0d1913, handle: 24 0x18
01:28:36.862 -> 224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,;16
01:28:36.862 -> [D][BLERemoteCharacteristic.cpp:434] readValue(): >> readValue(): uuid: 00010203-0405-0607-0809-0a0b0c0d1914, handle: 27 0x1b
01:28:36.929 -> 0,129,234,46,51,116,121,232,167,122,211,195,104,20,213,88,33,;17


OFF
01:32:03.612 -> [D][BLERemoteCharacteristic.cpp:462] readValue(): << readValue(): length: 1
01:32:03.612 -> 1,;1
01:32:03.612 -> [D][BLERemoteCharacteristic.cpp:434] readValue(): >> readValue(): uuid: 00010203-0405-0607-0809-0a0b0c0d1912, handle: 21 0x15
01:32:03.679 -> 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,;16
01:32:03.679 -> [D][BLERemoteCharacteristic.cpp:434] readValue(): >> readValue(): uuid: 00010203-0405-0607-0809-0a0b0c0d1913, handle: 24 0x18
01:32:03.745 -> 224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,;16
01:32:03.745 -> [D][BLERemoteCharacteristic.cpp:434] readValue(): >> readValue(): uuid: 00010203-0405-0607-0809-0a0b0c0d1914, handle: 27 0x1b
01:32:03.778 -> 0,196,191,114,168,30,93,135,146,26,10,126,254,62,173,225,34,;17


ON again: ?!??
                0,2,217,60,69,45,123,70,88,179,19,86,98,20,114,221,252,;17

00-02-D9-3C-45-2D-7B-46-58-B3-13-56-62-14-72-DD-FC

## IDE
https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/

IDE => installed from web: https://www.arduino.cc/en/Main/Software => https://www.arduino.cc/download_handler.php?f=/arduino-1.8.8-linux64.tar.xz
https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
installed new board manager => selected esp32 board

https://github.com/espressif/arduino-esp32

after installing board with tools/board/board-manager, select the board in the tools/board menu: ESP32 dev module

"es geht am besten mit dem Esp32 Dev Board. Die Baudrate von 115200 beachten"

## Drivers
https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
siliconlabs.force.com@maxant.co.uk / silicon11
unzipped download

    sudo apt-get install libelf-dev

then go to downloaded folder and read release notes:

    make
    sudo cp cp210x.ko /lib/modules/4.15.0-38-generic/kernel/drivers/usb/serial/
    sudo insmod /lib/modules/4.15.0-38-generic/kernel/drivers/usb/serial/usbserial.ko 
    sudo insmod cp210x.ko 

the middle command above had an error: 

    insmod: ERROR: could not insert module /lib/modules/4.15.0-38-generic/kernel/drivers/usb/serial/usbserial.ko: Invalid module format

restart arduino ide

in order to be able to use Serial (https://github.com/espressif/arduino-esp32/issues/13):

    sudo apt install python-pip
    pip install pyserial



https://www.arduino.cc/en/Guide/Troubleshooting#upload


project under ant/apps/arduino/001


## driver

https://iot.fkainka.de/driver => cannot make it compile


    lsusb

    => Bus 001 Device 005: ID 1a86:7523 QinHeng Electronics HL-340 USB-Serial adapter

http://playground.arduino.cc/Linux/All#Permission =>

added me to group according to instructions:

ant@hades-ubuntu:~$ ls -l /dev/ttyUSB*
crw-rw---- 1 root dialout 188, 0 Dez 13 21:16 /dev/ttyUSB0

=>

sudo usermod -a -G dialout ant


run the following just after plugging the usb in:

    dmesg | tail


	[  716.021554] usb 1-1.1: new full-speed USB device number 5 using ehci-pci
	[  716.131410] usb 1-1.1: New USB device found, idVendor=1a86, idProduct=7523
	[  716.131418] usb 1-1.1: New USB device strings: Mfr=0, Product=2, SerialNumber=0
	[  716.131422] usb 1-1.1: Product: USB2.0-Serial
	[  716.132161] ch341 1-1.1:1.0: ch341-uart converter detected
	[  716.133687] usb 1-1.1: ch341-uart converter now attached to ttyUSB0

start arduino ide

tools menu > port > ttyUSB0

toos menu > get board info => 

	BN: Unknown board
	VID: 1A86
	PID: 7523
	SN: Upload any sketch to obtain it

=> now able to upload sketches :-)

## Reinstall original firmware

https://iot.fkainka.de/nodeesp-firmware-reinstallieren

	pip install esptool

	git clone https://github.com/espressif/esptool.git

(done on /w/adventca...2018/esptool)

	cd esptool

so that esptool.py is available. then:

	/w/adventcalendar2018/esptool/esptool$

	sudo ./esptool.py -p /dev/ttyUSB1 write_flash -z 0x0 ~/Downloads/ESP32_FW.bin        <-- I CHANGED THE FILE NAME AS THERE IS A LATER BIN FILE!! FILES ARE IN THIS FOLDER

it outputs:

	esptool.py v2.6-beta1
	Serial port /dev/ttyUSB1
	Connecting.....
	Detecting chip type... ESP32
	Chip is ESP32D0WDQ6 (revision 1)
	Features: WiFi, BT, Dual Core, 240MHz, VRef calibration in efuse, Coding Scheme None
	MAC: 80:7d:3a:dc:56:10
	Uploading stub...
	Running stub...
	Stub running...
	Configuring flash size...
	Auto-detected Flash size: 4MB
	Compressed 4194304 bytes to 1340826...
	Wrote 4194304 bytes (1340826 compressed) at 0x00000000 in 121.2 seconds (effective 276.9 kbit/s)...
	Hash of data verified.

	Leaving...
	Hard resetting via RTS pin...

---
arduino IDE does this (taken when using debug output)

    python /home/ant/.arduino15/packages/esp32/tools/esptool/2.3.1/esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size detect 0xe000 /home/ant/.arduino15/packages/esp32/hardware/esp32/1.0.0/tools/partitions/boot_app0.bin 0x1000 /home/ant/.arduino15/packages/esp32/hardware/esp32/1.0.0/tools/sdk/bin/bootloader_qio_80m.bin 0x10000 /tmp/arduino_build_266402/music.ino.bin 0x8000 /tmp/arduino_build_266402/music.ino.partitions.bin 

---

then change wifi and connect to nodeesp

http://192.168.4.1/

setup wifi

go back to swisscom router

http://nodeesp.local/

check for firmware

reset udp to 192.168.1.255


