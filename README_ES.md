# Proyecto Monitoreo de cultivos

En este repositorio se encuentra el proyecto para medir variables de un cultivo 
tales como humedad del suelo, temperatura ambiente, nivel de luminosidad, CO (Monóxido de carbono)
y lluvia. Basado en el concepto IoT (internet of things), se obtienen los datos de los sensores,
se envian a la red para ser procesados y visualizados a través de una aplicación móvil.
Específicamente, los datos son enviados a una red local que contiene una base de datos, 
para ser almacenados,esto se hace con empleando una Raspberry Pi, Node-RED como comunicador 
y Maria DB para gestión de la base de datos. Después, esa misma base de datos es replicada en 
la nube, con el mismo esquema de Node-RED para que la aplicación acceda a los datos y sean
visualizados por el usuario. En el servicio local se dispone de una pantalla LCD para una
visualización  local de los datos, manejada por un procesador MicroBlaze implementado en una 
FPGA, que se encarga de comunicarse con la Raspberry a través de un puerto serial.


## Contenido del repositorio

**Programación de la etapa de sensado**
- 01_adquisicion_de _datos 


**Creación de base de datos**
- 02_base_de_datos


**Servidor en línea**
- 03_servidor_en_linea


**Servidor local**
- 04_servicio_local


**Aplicación móvil**
- 05_aplicacion_movil



## Programación de la estapa de sensado
En esta sección se encuenta el código implementado en el chip SoC de bajo costo y consumo de 
energía ESP32, que permite obtener datos de los cinco sensore para su posterior envío a la 
base de datos, a través del protocolo MQTT.

## Creación de base de datos
En esta sección se encuentra un script realizado en python e implementado en la Raspberry, 
que permite la creación de una base de datos en Maria DB, con dos tablas, de acuerdo a los
requerimientos específicos del proyecto. EL objetivo de las tablas son: 1) Una se encarga de
almacenar el histórico de los datos sensados, que será la tabla que emplearpa la etapa de 
aplicación móvil. 2) La otra se encarga de sobreescribir los datos para mostrar los últimos 
datos sensados, que será la tabla que empleará la sección de visualización local.

## Servidor en línea
En esta sección se encuentran los flujos empleados en Node-RED para el envío de los datos
sensados a las dos tablas de la base de datos, creadas para tal fin. En estos flujos se
muestran cada uno de los nodos requeridos para el envío de los datos obtenidos en la parte
de sensado a la base de datos, a través de nodos de comunicación MQTT.

## Servidor Local
1) Extracción de datos: En esta sección se encuenta un script en python, que se implementa en
   la Raspberry, con el fin de extraer los datos sensados y almacenados en la tabla 2 de la base
   de datos. Además de la extracción, el script se encarga de adecuar los datos obtenidos en una
   trama específica, para su lectura en la aplicación de la interfaz de la pantalla LCD.
2) Interfaz de visualización: Se adjunta el archivo .hdmi con el diseño de la interfaz gráfica
   de la pantalla LCD, realizada en el programa Nextión editor. También se adjuntan cada uno de
   los archivos .C, que contienen los algoritmos embebidos en los eventos de las funciones especí-
   ficas de cada una de las páginas que componen la interfaz de visualización. 
3) Control de la pantalla: 

## Aplicación móvil