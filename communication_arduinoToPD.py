import serial
import socket

#Port settings
ser = serial.Serial('COM5', 9600)
ser.flush()

# UDP socket settings
UDP_IP = "127.0.0.1"   # local address
UDP_PORT = 3333        # PD listening
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print("Listening to Arduino and sending to Pure Data...")

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()  #strip newline
        print("Received from Arduino:", line)

        # send to Pure Data
        sock.sendto(line.encode('utf-8'), (UDP_IP, UDP_PORT))
        print("Sent to PD:", line)
