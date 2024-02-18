import serial
import json
import time

# Open serial port
ser = serial.Serial('COM5', 9600)  # Adjust port and baud rate as needed

# Sample dictionary
data = {'key1': 123, 'key2': 'value2'}

# Serialize dictionary to JSON
serialized_data = json.dumps(data) + "\n"

# Send serialized data over serial
while True:
    ser.write(serialized_data.encode())
    time.sleep(1)

print("Ending")

# Close serial port
ser.close()
