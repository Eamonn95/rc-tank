# RC Tank

Laptop-controlled tracked robot project built around an Arduino MKR WiFi 1010, DRV8833 motor driver, and Raspberry Pi 3B+ for future FPV/video features.

## Current milestone

The first bench test is working:

**Laptop keyboard -> USB serial -> MKR WiFi 1010 -> DRV8833 -> DC motor**

Holding the space bar runs the motor and releasing it stops the motor.

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

The MKR is powered separately over USB from the laptop.

## Project structure

- `firmware/mkr_motor_control/mkr_motor_control.ino` - MKR serial motor controller
- `laptop-control/motor_control.py` - keyboard controller for Windows
- `docs/wiring.md` - wiring notes
- `hardware/parts-list.md` - current and planned hardware

## Roadmap

1. One-motor USB keyboard control - **working**
2. Add Wi-Fi control
3. Add second motor and differential steering
4. Add tracked chassis
5. Add watchdog/failsafe
6. Add Raspberry Pi 3B+ FPV camera stream
7. Add browser/gamepad control interface
8. Add battery and motor telemetry

## Safety

Motor power is supplied through the DRV8833, not from an MKR GPIO pin. The motor supply ground and MKR ground share a common reference through the DRV8833.
