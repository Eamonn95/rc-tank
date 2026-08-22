import socket
import threading
import time
from pynput import keyboard

# Replace this with the IP address printed by the MKR in Serial Monitor.
TARGET_IP = "192.168.1.123"
TARGET_PORT = 4210

HEARTBEAT_SECONDS = 0.10

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
motor_running = False
stop_event = threading.Event()


def send_command(command: bytes, repeat: int = 1):
    for _ in range(repeat):
        sock.sendto(command, (TARGET_IP, TARGET_PORT))
        if repeat > 1:
            time.sleep(0.02)


def heartbeat_loop():
    global motor_running
    while not stop_event.is_set():
        if motor_running:
            send_command(b"1")
        time.sleep(HEARTBEAT_SECONDS)


def on_press(key):
    global motor_running

    if key == keyboard.Key.space and not motor_running:
        motor_running = True
        send_command(b"1")
        print("MOTOR ON")


def on_release(key):
    global motor_running

    if key == keyboard.Key.space:
        motor_running = False
        # Send STOP a few times because UDP does not guarantee delivery.
        send_command(b"0", repeat=3)
        print("MOTOR OFF")

    if key == keyboard.Key.esc:
        motor_running = False
        send_command(b"0", repeat=5)
        stop_event.set()
        return False


def main():
    thread = threading.Thread(target=heartbeat_loop, daemon=True)
    thread.start()

    print(f"Sending commands to {TARGET_IP}:{TARGET_PORT}")
    print("Hold SPACE to run motor")
    print("Release SPACE to stop")
    print("Press ESC to quit")

    try:
        with keyboard.Listener(on_press=on_press, on_release=on_release) as listener:
            listener.join()
    finally:
        stop_event.set()
        send_command(b"0", repeat=5)
        sock.close()


if __name__ == "__main__":
    main()
