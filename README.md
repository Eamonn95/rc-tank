# RC Tank

Laptop-controlled tracked robot project built around an Arduino MKR WiFi 1010, DRV8833 motor driver, and Raspberry Pi 3B+ for future FPV/video features.

## Current milestone

The one-motor bench test is working over USB serial:

**Laptop keyboard -> USB serial -> MKR WiFi 1010 -> DRV8833 -> DC motor**

Holding the space bar runs the motor and releasing it stops the motor.

Wi-Fi control code has now been added and is ready for bench testing:

**Laptop keyboard -> Wi-Fi UDP -> MKR WiFi 1010 -> DRV8833 -> DC motor**

The Wi-Fi version includes a 500 ms motor failsafe if control packets stop arriving.

## Current hardware

- Arduino MKR WiFi 1010
- DRV8833 dual H-bridge motor driver
- 1 small brushed DC motor (OSEPP LS-00025)
- 2x AA batteries in series for ~3 V motor power
- Windows laptop
- Raspberry Pi 3B+ reserved for future FPV/video

## Confirmed one-motor wiring

| MKR WiFi 1010 | DRV8833 |
| --- | --- |
| Pin 5 | AIN1 |
| Pin 4 | AIN2 |
| VCC (3.3 V) | SLP |
| GND | GND |

| DRV8833 | Motor / supply |
| --- | --- |
| AOUT1 | Motor wire 1 |
| AOUT2 | Motor wire 2 |
| VMOTOR + | 2x AA battery pack + |
| VMOTOR - | 2x AA battery pack - |

The MKR is powered separately over USB during setup/testing.

## Project structure

- `firmware/mkr_motor_control/mkr_motor_control.ino` - working USB serial motor controller
- `firmware/mkr_wifi_motor_control/mkr_wifi_motor_control.ino` - Wi-Fi UDP motor controller with failsafe
- `firmware/mkr_wifi_motor_control/arduino_secrets.example.h` - Wi-Fi credentials template
- `laptop-control/motor_control.py` - working USB keyboard controller for Windows
- `laptop-control/wifi_motor_control.py` - Wi-Fi keyboard controller
- `docs/wiring.md` - wiring notes
- `docs/wifi-control.md` - Wi-Fi setup instructions
- `hardware/parts-list.md` - current and planned hardware

## Roadmap

1. One-motor USB keyboard control - **working**
2. One-motor Wi-Fi keyboard control - **ready to test**
3. Add second motor and differential steering
4. Add tracked chassis
5. Expand failsafe and emergency-stop behavior
6. Add Raspberry Pi 3B+ FPV camera stream
7. Add browser/gamepad control interface
8. Add battery and motor telemetry

## Safety

Motor power is supplied through the DRV8833, not from an MKR GPIO pin. The motor supply ground and MKR ground share a common reference through the DRV8833.

The Wi-Fi controller stops the motor if control packets are lost for more than 500 ms. The current UDP prototype is intended for a trusted/private local network and does not yet authenticate control packets.
