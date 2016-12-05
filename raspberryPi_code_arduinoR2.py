import RPi.GPIO as GPIO ## Import GPIO library
import time ## Import 'time' library. Allows us to use 'sleep'
import serial
import socket

HOST = '192.168.1.136'
RPORT = 12345
TPORT = 12347
RxSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
TxSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

print('Socket Created')

GPIO.setmode(GPIO.BOARD) ## Use board pin numbering
GPIO.setup(32, GPIO.OUT) ## Setup GPIO Pin 7 to OUT

ser = serial.Serial('/dev/ttyUSB0',9600, timeout=0, writeTimeout=0)
print("The code is running!")

try:
	RxSock.bind((HOST,RPORT))
except socket.error:
	print("Bind Failed")

try:
	TxSock.bind((HOST,TPORT))
except socket.error:
	print("Bind Failed")

RxSock.listen(1)
print 'Socket awaiting messages'
(conn,addr) = RxSock.accept()
# TxSock.accept()
print 'Connected'

while True:
    wifi_data = conn.recv(1024)
    ser_data = ser.readline()
    if wifi_data is not None:
        print("This is the data " + str(wifi_data))
        ser.write(wifi_data)
        print("This is being sent " + str(ser_data))
        # TxSock.send(ser_data)
        time.sleep(0.05)
        RxSock.send(ser_data)

conn.close()