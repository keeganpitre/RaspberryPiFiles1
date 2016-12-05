import RPi.GPIO as GPIO ## Import GPIO library
import time ## Import 'time' library. Allows us to use 'sleep'
import serial
import socket
from flask import Flask
app = Flask(__name__)

@app.route("/<data>")
def flask_function(data):
    global ser
    ser.write(data)
    time.sleep(0.05)
    if '+1' in data:
        return ser.readline()
    else:
        something = "OK"
        return something

@app.route("/")
def just_return():
    return 'I am running'

if __name__ == "__main__":
    global ser
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=0, writeTimeout=0)
    app.run(host='0.0.0.0', port=5000)