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



ser = serial.Serial("/dev/ttyS0",9600,timeout=1)

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
	print(values)

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

	print(lst)	
	print(lst_to_send)

	#Se dividen los datos en string, para eso primero se divide la lista y luego es 
	#convertida en string con un formato definido
	plant1_send = conver_str(lst_to_send[0:9])
	plant2_send = conver_str(lst_to_send[9:18])
	plant3_send = conver_str(lst_to_send[18:27])
	plant4_send = conver_str(lst_to_send[27:36])

	print("Planta 1: " + plant1_send)
	print("Planta 2: " + plant2_send)
	print("Planta 3: " + plant3_send)
	print("Planta 4: " + plant4_send)

	ser.write(plant1_send.encode())
	time.sleep(5)
	ser.write(plant2_send.encode())	
	time.sleep(5)
	ser.write(plant3_send.encode())	
	time.sleep(5)
	ser.write(plant4_send.encode())		
	time.sleep(5)
	
	#if(ser.in_waiting > 0):
    #	line = ser.readline().decode()
    #    print(line)





db.close()
