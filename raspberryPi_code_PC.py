import time ## Import 'time' library. Allows us to use 'sleep'
import serial
import socket

HOST = '192.168.1.136'
PORT = 12345

RxSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

RxSock.connect((HOST,PORT))


print("The code is running!")

z=0

while z==0:
    var = raw_input("Please enter something: ")
    print(var)
    RxSock.send(var)





