import serial
import time

ser = serial.Serial('/dev/ttyACM0',115200)
ser.write('4')
time.sleep(1)
ser.write('3')
