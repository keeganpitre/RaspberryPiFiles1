import RPi.GPIO as GPIO ## Import GPIO library
import time ## Import 'time' library. Allows us to use 'sleep'
import serial
import socket
from flask import Flask
app = Flask(__name__)

@app.route("/<data>")
def flask_function(data):
    global ser
    return 'hello'

    ser.write(data)
    return ser.readline()


if __name__ == "__main__":
    global ser
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=0, writeTimeout=0)
    app.run()