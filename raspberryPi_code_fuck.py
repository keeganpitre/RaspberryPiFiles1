import serial
import time
import sys
import requests
from flask import Flask,render_template, request, url_for

req = requests.get("http://192.168.1.136:5000/snd/+1", auth=('user', 'pass'))
print(req.content)