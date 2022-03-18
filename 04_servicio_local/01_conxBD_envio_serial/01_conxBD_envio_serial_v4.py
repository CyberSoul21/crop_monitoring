#/**************************************************************************//**
# * @file 01_conxBD_envio_serial.py
# *
# *
# * @authors:
# * Wilson Javier Almario Rodriguez.
# * Diana Natali Maldonado Ramirez
# * Camilo Andres Garzon Lopez
# * Wendy Alejandra Garcia Rojas
# * Sebastian Betancour Peñaranda
# *
# * @date 06/29/2020
# *
# *
# *
# *****************************************************************************/
#/******************************************************************************
# * Copyright (C) 2020 by Monitoreo de cultivo
# *****************************************************************************/



#!/usr/bin/env python3

#sudo python3 -m pip install PyMySQL



#Run a Program At Startup:
#Editing rc.local
#sudo nano /etc/rc.local
#Add commands to execute the python program, before exit 0
#sudo python /home/pi/testAtoExecute.py &
#Killing process: pkill -f testAtoExecute.py
#https://www.dexterindustries.com/howto/run-a-program-on-your-raspberry-pi-at-startup/
#https://janakiev.com/blog/python-background/



import pymysql #Libreria para conectar con MariaDB
import datetime
import serial
import time



#ser = serial.Serial("/dev/ttyS0",9600,timeout=1)

num_sensor = 4 #En caso de agregar o quitar un sensor, modificar esta variable

def range_temp(t): #Definir rango de operación para la temperatura
	if t > 10 and t < 20:
		return 1
	elif t <= 10 or t >= 20:
		return 0

def range_hum(h): #Definir rango de operación para la Humedad
	if h > 10 and h < 20:
		return 1
	elif h <= 10 or h >= 20:
		return 0

def range_co2(c): #Definir rango de operación para el CO2
	if c > 10 and c < 20:
		return 1
	elif c <= 10 or c >= 20:
		return 0

def range_lum(l): #Definir rango de operación para la luminicencia
	if l > 10 and l < 20:
		return 1
	elif l <= 10 or l >= 20:
		return 0

def selec(c): #Segun la seleccion de la variable
    switcher = {
        1: range_temp(c),
        2: range_hum(c),
        3: range_co2(c),
        4: range_lum(c),
    }
    return switcher.get(c, "Invalid month")

def conver_str(lst): #Conversión de lista a string en un formato definido
	lst_str=""
	for x in lst:
		if lst_str == "":
			lst_str = str(x)
		else:
			lst_str = lst_str + ":" + str(x)

	return lst_str

#db = pymysql.connect("mynodered.ddns.net","usuariow","usuariow","monitoreo") # Conector (direccion, usuario, contraseña, nombre_BD)
#cu = db.cursor()# Declaracion del cursor

while True:

	db = pymysql.connect("mynodered.ddns.net","usuariow","usuariow","monitoreo") # Conector (direccion, usuario, contraseña, nombre_BD)
	cu = db.cursor()# Declaracion del cursor

	cu.execute("SELECT Planta, Valor FROM monitoreo2") # Se extraen los valores de la columan llamada "Valor"
	values = cu.fetchall()
	#print(values)

	num_data = len(values)

	num_plant = num_data/num_sensor # obtener el numero de plantas, para automatizar

	count = 0
	lst = []
	for i in values: #los valores almacenados en la tupla, se guardan en una lista lst

		if count == 0:
			lst.append(i[0])
		if count < num_sensor:
			lst.append(i[1])
			count +=1
		elif count == num_sensor:
			lst.append(i[0])
			lst.append(i[1])
			count = 1

	lst_to_send =[]
	lim = num_sensor + 1
	count = 0 #Conteo para saber en que planta y que variable tomar
	for j in lst: #se crea una lista que contiene las variables con su respectivo identificador lst_to_send

		if count == 0: #Para que no tome el itentificador de la planta
			lst_to_send.append(j)
			count +=1
		elif count < lim and count > 0:
			lst_to_send.append(j)
			lst_to_send.append(selec(count)) #se agrega el identificador a cada variable
			count +=1
		elif count == lim:
			lst_to_send.append(j)
			count = 1

	#Se dividen los datos en string, para eso primero se divide la lista y luego es
	#convertida en string con un formato definido
	#plant1_send = conver_str(lst_to_send[0:9])
	p1t = "t1i"+conver_str(lst_to_send[1:2])+"f"
	h1 = conver_str(lst_to_send[3:4])
	H1 = float(h1)
	y1 = int(H1)
	if y1<10:
		ph1 = "000" + str(y1) + "f"
	elif y1>9 and y1<100:
		ph1 = "00" + str(y1) + "f"
	elif y1>99:
		ph1 = "0" +str(y1) + "f"

	p1h = "h1i"+ ph1
	p1c = "c1i"+conver_str(lst_to_send[7:8])+"f"
	l1 = conver_str(lst_to_send[5:6])
	L1 = float(l1)
	x1=int(L1)
	#print(x)
	if x1 == 1:
		pl1 = "111"
	elif x1 ==0:
		pl1 = "000"

	p1l="l1i"+str(x1)+pl1+"f"

	#inicia planta 2
	p2t = "t2i"+conver_str(lst_to_send[10:11])+"f"
	h2 = conver_str(lst_to_send[12:13])
	H2 = float(h2)
	y2 = int(H2)
	if y2<10:
		ph2 = "000" + str(y2) + "f"
	elif y2>9 and y2<100:
		ph2 = "00" + str(y2) + "f"
	elif y2>99:
		ph2 = "0"+str(y2) + "f"

	p2h = "h2i"+ ph2
	p2c = "c2i"+conver_str(lst_to_send[16:17])+"f"
	l2 = conver_str(lst_to_send[14:15])
	L2 = float(l2)
	x2=int(L2)
	#print(x)
	if x2 == 1:
		pl2 = "111"
	elif x2 ==0:
		pl2 = "000"

	p2l="l2i"+str(x2)+pl2+"f"

	#inicia planta 3
	p3t = "t3i"+conver_str(lst_to_send[19:20])+"f"
	h3 = conver_str(lst_to_send[21:22])
	H3 = float(h3)
	y3 = int(H3)
	if y3<10:
		ph3 = "000" + str(y3) + "f"
	elif y3>9 and y3<100:
		ph3 = "00" + str(y3) + "f"
	elif y3>99:
		ph3 = "0"+str(y3) + "f"

	p3h = "h3i"+ ph3
	p3c = "c3i"+conver_str(lst_to_send[25:26])+"f"
	l3 = conver_str(lst_to_send[23:24])
	L3 = float(l3)
	x3=int(L3)
	#print(x)
	if x3 == 1:
		pl3 = "111"
	elif x3 ==0:
		pl3 = "000"

	p3l="l3i"+str(x3)+pl3+"f"

	#inicia planta 4
	p4t = "t4i"+conver_str(lst_to_send[28:29])+"f"
	h4 = conver_str(lst_to_send[30:31])
	H4 = float(h4)
	y4 = int(H4)
	if y4<10:
		ph4 = "000" + str(y4) + "f"
	elif y4>9 and y4<100:
		ph4 = "00" + str(y4) + "f"
	elif y4>99:
		ph4 = "0"+str(y4) + "f"

	p4h = "h4i"+ ph4
	p4c = "c4i"+conver_str(lst_to_send[34:35])+"f"
	l4 = conver_str(lst_to_send[32:33])
	L4 = float(l4)
	x4=int(L4)
	#print(x)
	if x4 == 1:
		pl4 = "111"
	elif x4 ==0:
		pl4 = "000"

	p4l="l4i"+str(x4)+pl4+"f"

	#lluvia
	a0 = conver_str(lst_to_send[37:38])
	A0 = float(a0)
	x0=int(A0)
	#print(x)
	if x0 == 1:
		pa0 = "111"
	elif x0 ==0:
		pa0 = "000"

	p0a="a0i"+str(x0)+pa0+"f"

	#plant2_send = conver_str(lst_to_send[9:18])
	#plant3_send = conver_str(lst_to_send[18:27])
	#plant4_send = conver_str(lst_to_send[27:36])
	print(p1t)
	print(p1h)
	print(p1c)
	print(p1l)
	print(p2t)
	print(p2h)
	print(p2c)
	print(p2l)
	print(p3t)
	print(p3h)
	print(p3c)
	print(p3l)
	print(p4t)
	print(p4h)
	print(p4c)
	print(p4l)
	print(p0a)
	#print("Planta 1: " + plant1_send)
	#print("Planta 2: " + plant2_send)
	#print("Planta 3: " + plant3_send)
	#print("Planta 4: " + plant4_send)

	ser.write(p1t.encode())
	time.sleep(5)
	ser.write(p1h.encode())
	time.sleep(5)
	ser.write(p1c.encode())
	time.sleep(5)
	ser.write(p1l.encode())
	time.sleep(5)
	ser.write(p2t.encode())
	time.sleep(5)
	ser.write(p2h.encode())
	time.sleep(5)
	ser.write(p2c.encode())
	time.sleep(5)
	ser.write(p2l.encode())
	time.sleep(5)
	ser.write(p3t.encode())
	time.sleep(5)
	ser.write(p3h.encode())
	time.sleep(5)
	ser.write(p3c.encode())
	time.sleep(5)
	ser.write(p3l.encode())
	time.sleep(5)
	ser.write(p4t.encode())
	time.sleep(5)
	ser.write(p4h.encode())
	time.sleep(5)
	ser.write(p4c.encode())
	time.sleep(5)
	ser.write(p4l.encode())
	time.sleep(5)
	ser.write(p0a.encode())
	time.sleep(5)
	#if(ser.in_waiting > 0):
    #	line = ser.readline().decode()
    #    print(line)





db.close()
