# Wiring

## Current one-motor bench setup

### Arduino MKR WiFi 1010 -> DRV8833

| MKR | DRV8833 | Purpose |
| --- | --- | --- |
| Pin 5 | AIN1 | Motor channel A control input 1 |
| Pin 4 | AIN2 | Motor channel A control input 2 |
| VCC (3.3 V) | SLP | Keeps driver enabled |
| GND | GND | Common logic ground |

### Motor -> DRV8833

| Motor | DRV8833 |
| --- | --- |
| Wire 1 | AOUT1 |
| Wire 2 | AOUT2 |

The motor does not have a permanent positive and negative lead. The DRV8833 reverses polarity across AOUT1/AOUT2 to reverse motor direction.

### Motor power

Two AA batteries are connected **in series** for approximately 3 V.

| Battery pack | DRV8833 |
| --- | --- |
| Positive | VMOTOR + |
| Negative | VMOTOR - / GND |

The MKR is powered from the laptop over USB.

## Important notes

- Do not power the motor from an MKR GPIO pin.
- Keep SLP high at 3.3 V while using the driver.
- MKR GND and DRV8833 GND must share a common reference.
- The current OSEPP LS-00025 motor is a small low-voltage test motor; use geared motors for the tracked chassis later.
