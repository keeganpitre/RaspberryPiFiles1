import RPi.GPIO as GPIO ## Import GPIO library
import time ## Import 'time' library. Allows us to use 'sleep'
import serial
import socket

HOST = '192.168.1.136'
RPORT = 12345
TPORT = 12346

RxSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
TxSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

print('Socket Created')

GPIO.setmode(GPIO.BOARD) ## Use board pin numbering
GPIO.setup(32, GPIO.OUT) ## Setup GPIO Pin 7 to OUT

ser = serial.Serial('/dev/ttyUSB0',9600, timeout=0, writeTimeout=0)
print("The code is running!")

try:
	RxSockk.bind((HOST,RPORT))
except socket.error:
	print("Bind Failed")

try:
	TxSock.bind((HOST,TPORT))
except socket.error:
	print("Bind Failed")

RxSock.listen(1)
print 'Socket awaiting messages'
(conn,addr) = RxSock.accept()
print 'Connected'

z=0


while z==0:
    data = conn.recv(1024)
    print("This is the data " + str(data))
    ser.write(data)


conn.close()