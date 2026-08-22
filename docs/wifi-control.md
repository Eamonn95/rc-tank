# Wi-Fi motor control test

This keeps the confirmed one-motor wiring exactly the same and replaces the USB serial control link with Wi-Fi UDP commands.

## Hardware wiring

- MKR pin 5 -> DRV8833 AIN1
- MKR pin 4 -> DRV8833 AIN2
- MKR VCC (3.3 V) -> DRV8833 SLP
- MKR GND -> DRV8833 GND
- DRV8833 AOUT1/AOUT2 -> motor wires
- 2x AA batteries in series -> DRV8833 VMOTOR + / -
- MKR powered by USB during setup/testing

## 1. Install the Arduino Wi-Fi library

In Arduino IDE, open Library Manager and make sure `WiFiNINA` is installed.

## 2. Add local Wi-Fi credentials

In `firmware/mkr_wifi_motor_control/`, copy:

`arduino_secrets.example.h`

to:

`arduino_secrets.h`

Then replace the placeholders with your Wi-Fi name and password. `arduino_secrets.h` is ignored by git so the password is not committed.

## 3. Upload the Wi-Fi firmware

Open `mkr_wifi_motor_control.ino`, select Arduino MKR WiFi 1010, and upload.

Open Serial Monitor at 115200 baud. After connecting, the MKR prints its IP address, for example:

`MKR IP address: 192.168.1.42`

## 4. Configure the laptop controller

Open `laptop-control/wifi_motor_control.py` and change:

`TARGET_IP = "192.168.1.123"`

to the IP address printed by the MKR.

The laptop and MKR must be on the same Wi-Fi network.

Install pynput if needed:

`py -m pip install pynput`

Then run:

`py wifi_motor_control.py`

## Controls

- Hold Space: motor runs forward
- Release Space: motor stops
- Esc: stop motor and exit

## Failsafe

While Space is held, the laptop sends a heartbeat command every 100 ms. If the MKR goes 500 ms without a valid drive packet, it automatically stops the motor. If Wi-Fi disconnects, the MKR also stops the motor before reconnecting.

For this prototype, use only a trusted/private Wi-Fi network. The UDP command channel does not yet authenticate the sender.
