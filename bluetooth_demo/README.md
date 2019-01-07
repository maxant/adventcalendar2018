

https://www.npmjs.com/package/noble-extended

    sudo apt-get install bluetooth bluez libbluetooth-dev libudev-dev


as work around for bluetooth-hci-socket not able to be installed with npm and node 10:

    npm install "https://github.com/jrobeson/node-bluetooth-hci-socket/#fix-builds-for-node-10"

doesnt work with thinkpad bluetooth as its not BLE

bluetooth dongle: 

    lsusb

seems to be device with ID `2687:fb01`.

https://wiki.ubuntu.com/HardwareSupportComponentsBluetoothUsbAdapters

    hciconfig

=> no results

https://www.maketecheasier.com/setup-bluetooth-in-linux/

    sudo rfkill unblock bluetooth


