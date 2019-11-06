# attack25_ble

"ATTACK25_BLE" is a 5×5 key keyboard "ATTACK25" that can be used with Bluetooth connection using "BLE Micro Pro".

Keyboard Maintainer (original): [monksoffunk](https://github.com/monksoffunk/qmk_firmware/blob/attack25/keyboards/attack25/readme.md)  
Hardware Supported: ATTACK25 PCBs  
Hardware Availability: 
- ATTACK25
  - [25KEYS - BOOTH](https://25keys.booth.pm/)
- BLE Micro Pro: 
  - [Pro MicroサイズのUSB対応nRF52マイコンボード - のぎけす屋 - BOOTH](https://nogikes.booth.pm/items/1177319) 
  - [BLE Micro Pro | 遊舎工房](https://yushakobo.jp/shop/ble-micro-pro/)

Make example for this keyboard (after setting up your build environment):

1. Look at the "BLE Micro Pro (BMP)" page and prepare the build environment.
1. Download BMP bootloader and compiled firmware.
1. Write the boot loader to BMP.
1. Write the compiled firmware to BMP.
1. Confirm that ATTACK25 is recognized as a mass storage device.
1. Edit the `CONFIG.JSN` file in ATTACK25 to customize the config.
1. Edit the `KEYMAP.JSN` file in ATTACK25 to customize the keymap.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).


*** To use this keymap, custom firmware must be written to Attack25. The custom firmware is `ble_micro_pro_attack25_ble.zip` in the same directory as this` readme.md` file.
Custom firmware can be written with the following command:

`nrfutil dfu usb-serial -pkg ble_micro_pro_attack25_ble.zip -p / dev / tty.usbmodem0000000000011`

Note: For `/ dev / tty.usbmodem0000000000011`, specify the“ Attack25 ”serial port in your environment.