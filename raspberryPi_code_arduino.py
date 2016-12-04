import RPi.GPIO as GPIO ## Import GPIO library
import time ## Import 'time' library. Allows us to use 'sleep'

GPIO.setmode(GPIO.BOARD) ## Use board pin numbering
GPIO.setup(32, GPIO.OUT) ## Setup GPIO Pin 7 to OUT

ser = serial.Serial('/dev/ttyUSB0',9600, timeout=0, writeTimeout=0)

print("The code is running!")

z=0

while z==0:
    var = raw_input("Please enter something: ")
    print(var)
    ser.write(var)
    