#!/usr/bin/env python3

#Run a Program At Startup:
#Editing rc.local
#sudo nano /etc/rc.local
#Add commands to execute the python program, before exit 0
#sudo python /home/pi/testAtoExecute.py &
#Killing process: pkill -f testAtoExecute.py
#https://www.dexterindustries.com/howto/run-a-program-on-your-raspberry-pi-at-startup/
#https://janakiev.com/blog/python-background/

import serial, time
ser = serial.Serial("/dev/ttyS0",9600,timeout=1)
salu = "ghhryu\n\r"
empty=" "
while True:

#	print(ser.readline().decode())
	ser.write(salu.encode())
	time.sleep(1)
	if (ser.in_waiting > 0):
           line = ser.readline().decode()
           print(line)

