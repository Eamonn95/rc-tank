import serial
import time
from pynput import keyboard

# Change this to the COM port shown in Arduino IDE: Tools -> Port
PORT = "COM4"
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=1)
time.sleep(2)

motor_running = False


def on_press(key):
    global motor_running

    if key == keyboard.Key.space and not motor_running:
        ser.write(b"1")
        motor_running = True
        print("MOTOR ON")


def on_release(key):
    global motor_running

    if key == keyboard.Key.space:
        ser.write(b"0")
        motor_running = False
        print("MOTOR OFF")

    if key == keyboard.Key.esc:
        ser.write(b"0")
        ser.close()
        return False


print("Hold SPACE to run motor")
print("Release SPACE to stop")
print("Press ESC to quit")

with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
    listener.join()
