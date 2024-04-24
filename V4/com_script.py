# Auth: Jatan Pandya

import serial
import time

COM_PORT = 'COM19'
BAUD_RATE = 115200
FILE_NAME = "sine_1.25Hz.txt"
SAMPLE_TIME = 0.007

def open_serial_port():
    try:
        ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
        return ser
    except serial.SerialException as e:
        print(f"Failed to open serial port {COM_PORT}: {e}")
        return None

def read_file(ser):
    try:
        with open(FILE_NAME, 'r') as file:
            for line in file:
                line = line.strip() 
                send_data(line, ser)
                time.sleep(SAMPLE_TIME)
    except FileNotFoundError as e:
        print(f"Failed to open file {FILE_NAME}: {e}")

def send_data(data, ser):
    try:
        if ser:
            ser.write(data.encode())  
            ser.write(b'\n') 
        else:
            print("Serial port is not open. Cannot send data.")
    except serial.SerialException as e:
        print(f"Failed to send data over serial port: {e}")

def main():
    user_input = input("Do you want to run the file? (y/n): ").strip().lower()
    if user_input == 'y':
        ser = open_serial_port()
        print("Running...")
        if not ser:
            return
        read_file(ser)
        ser.close()
        print("Completed!")
    elif user_input == 'n':
        print("script stopped")
    else:
        print("Invalid input. Please enter 'y' or 'n'.")

if __name__ == "__main__":
    main()