import serial
import time

COM_PORT = 'COMX'  
BAUD_RATE = 115200

ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)

time.sleep(2)

def send_command(command):
    ser.write(command.encode())
    time.sleep(0.1)
    response = ser.read_all().decode()
    return response

def main():
    print("1. List files on SPIFFS")
    choice = input("Enter your choice: ")

    if choice == "1":
        print("Requesting file list from ESP32...")
        response = send_command("list_files\n")
        print(response)

    ser.close()

if __name__ == "__main__":
    main()
