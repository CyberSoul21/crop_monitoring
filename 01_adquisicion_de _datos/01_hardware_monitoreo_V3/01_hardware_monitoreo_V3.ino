
/**************************************************************************//**
 * @file hardware_monitoreo_V3.ino
 *
 * 
 * @authors: 
 * Wilson Javier Almario Rodriguez.
 * Diana Natali Maldonado Ramirez
 * Camilo Andres Garzon Lopez
 * Wendy Alejandra Garcia Rojas
 * Sebastian Betancour Peñaranda
 * 
 * @date 06/29/2020
 *
 *
 *
 *****************************************************************************/
/******************************************************************************
 * Copyright (C) 2020 by Monitoreo de cultivo 
 *****************************************************************************/


/*=============================== LIBRERÍAS UTILIZADAS =======================================*/
#include "DHT.h"                        //Se agrega la librearia del sensor DHT11
#include "Adafruit_MQTT.h"              //Se agregan las librerias para la comunicación MQTT 
#include "Adafruit_MQTT_Client.h"
#include <WiFi.h>                       //Se agrega la librearia para la comunicación WiFi
#include <NTPClient.h>                  //Se agrega libreria WiFi para adquisición de fecha y hora (Protocolo NTP)
#include <WiFiUdp.h>                    

/*============================ DATOS DE ACCESO A LA RED WIFI ================================*/
#define WLAN_SSID   "FUENTES"           //Nombre de la red WiFi
#define WLAN_PASS   "10266898A"         //Contraseña de la red WiFi

/*================ PREPARANDO CLIENTE NTP PARA TIMESTAMP (MARCA DE TIEMPO) ==================*/
WiFiUDP ntpUDP;                         //Se define cliente para obtener fecha y hora
NTPClient timeClient(ntpUDP);

/*============================== DEFINICIÓN DE PINES ========================================*/
#define DHTPIN 15                       //Se define el PIN del ESP32 al que va el sensor DHT11 (GPIO15)
#define DHTTYPE DHT11                   //Se define el tipo del sensor (DHT11)
DHT dht(DHTPIN, DHTTYPE);               //Se define una instanciaResultados  para el sensor DHT11

float sensorPin_Luz= 39;                //Se define el PIN del ESP32 al que va el sensor de luz (PIN Vn, GPIO39)
int sensorPin_Humedad = 36;             //Se define el PIN del ESP32 al que va el sensor de humedad (PIN Vp, GPIO36)
float sensorPin_CO= 4;                  //Se define el PIN del ESP32 al que va el sensor de CO (GPIO4)
const int sensorPin_Lluvia = 5;         //Se define el PIN del ESP32 al que va el sensor de Lluvia (GPIO5)

/*======================= INICIALIZACIÓN DE VARIABLES DE LECTURA ============================*/
float Luz = 0;
int Humedad=0;
float CO=0;
int Lluvia = 0;

/*========== DECLARACIÓN DE VARIABLES CADENA PARA CONCATENAR DATOS DE CADA SENSOR ===========*/
String formattedDate;
String dayStamp;
String timeStamp;
String Humedad_c;
String Temperatura_c;
String Luz_c;
String CO_c;

/*========================= DATOS DEL RECEPTOR DE MQTT =================================*/
//Configuración del receptor de MQTT  
#define HOST        "agronet.ddns.net"  //Dominio del host
#define PORT        1883                //Puerto donde está instalada el MQTT
#define USERNAME    "esp32"             //Usuario MQTT
#define PASSWORD    "esp32"             //Contraseña de MQTT
const int timeout = 200;                //Conteo de tiempo de espera para conexión MQTT

/*======================= DEFINICIÓN DEL OBJETO PRINCIPAL MQTT ===========================*/
WiFiClient client;                      //Se crea una clase de tipo WiFiClient para el ESP32 para conectarse al servidor MQTT.  
Adafruit_MQTT_Client mqtt(&client, HOST, PORT, USERNAME, PASSWORD); //Se configura la clase de cliente MQTT pasando el cliente WiFi y el servidor MQTT y los detalles de inicio de sesión.    

/*============ CONFIGURACIÓN DE VARIABLES Y TOPICS PARA PUBLICACIÓN POR MQTT =============*/
//Se definen "variables" de tipo "Adafruit_MQTT_Publish" para cada dato
//Estas variables reciben "&clienteMQTT" y el topic de publicación de la forma "G1/Variable_Planta_TablaDeLaBD"
Adafruit_MQTT_Publish Temperatura_B1 = Adafruit_MQTT_Publish(&mqtt, "/G1/Temperatura_P2_B1");
Adafruit_MQTT_Publish Humedad_B1 = Adafruit_MQTT_Publish(&mqtt, "/G1/Humedad_P2_B1");
Adafruit_MQTT_Publish Luz_B1 = Adafruit_MQTT_Publish(&mqtt, "/G1/Luz_P2_B1");
Adafruit_MQTT_Publish CO_B1 = Adafruit_MQTT_Publish(&mqtt, "/G1/CO_P2_B1");
Adafruit_MQTT_Publish Temperatura_B2 = Adafruit_MQTT_Publish(&mqtt, "/G1/Temperatura_P2_B2");
Adafruit_MQTT_Publish Humedad_B2 = Adafruit_MQTT_Publish(&mqtt, "/G1/Humedad_P2_B2");
Adafruit_MQTT_Publish Luz_B2 = Adafruit_MQTT_Publish(&mqtt, "/G1/Luz_P2_B2");
Adafruit_MQTT_Publish CO_B2 = Adafruit_MQTT_Publish(&mqtt, "/G1/CO_P2_B2");
Adafruit_MQTT_Publish Lluvia_B2 = Adafruit_MQTT_Publish(&mqtt, "/G1/Lluvia");

//Se debe declarar esta función inicialmente para arreglar un bug
void MQTT_connect();                   

/*================================== SETUP =============================================*/
void setup() { 
  delay(1); 
  
  //Modo estación
  WiFi.mode(WIFI_STA);   

  //Configuración del puerto serial   
  Serial.begin(115200); 

  //Conexión al punto de acceso WiFi                                           
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  //Inicialización de la conexión WiFi
  WiFi.begin(WLAN_SSID, WLAN_PASS);                                  
  int i = 0;
  for (; i < timeout; i++)
  {
    if(WiFi.status() == WL_CONNECTED) break;
    delay(100);
    Serial.print(".");
  }
  if(i == timeout)
    Serial.println("No Conectado");
    Serial.println("IP address: "); Serial.println(WiFi.localIP());

  //Inicializaciones
  timeClient.begin();                          //Inicialización del cliente NTP para obtener fecha y hora del servidor NTP
  timeClient.setTimeOffset(-18000);            //Selección zona horaria. GTM -5 = -18000 para Colombia
  dht.begin();                                 //Inicialización del sensor DHT11
}

/*================================ LOOP =============================================*/
void loop() 
{
  //Las siguientes líneas aseguran que obtengamos una fecha y hora válidas:
  while(!timeClient.update())                 
  {
    timeClient.forceUpdate();                                        
  }  
  //Conversión de la fecha y la hora a un formato legible
  formattedDate = timeClient.getFormattedDate();

  //Inicialización de la conexión MQTT: Asegura que la conexión al servidor MQTT esté activa (esto hará la primera
  // conexión y la reconexión automática cuando se desconecta). Ver el MQTT_connect definición de la función más abajo.
  MQTT_connect();                              

  /******* Lectura de sensores y configuración de dicha lectura *******/
  //Luz
  float Luz_lectura = analogRead(sensorPin_Luz)/4;              
  if (Luz_lectura < 500){
    Luz = 1;
    } else {
    Luz = 0;  
    }
  //Humedad  
  int Humedad = (1024-analogRead(sensorPin_Humedad)/4)/6.55;
  //Temperatura
  float Temperatura = dht.readTemperature();
  //Monóxido de carbono
  float CO= analogRead(sensorPin_CO)/1024*5.0;
  //Lluvia
  float Lluvia_lectura = digitalRead(sensorPin_Lluvia);
  if (Lluvia_lectura == LOW) {
      Serial.println("Lluvia detectada");
      Lluvia =1;
  } else {
     Serial.println("Lluvia no detectada");
     Lluvia =0;
    }
    
  //Verifiación de cualquier falla de lecura y descononexión del sensor DHT11
  if (isnan(Temperatura)) {                                 
     Serial.println("Failed to read from DHT sensor!");
    return;
  }

  //Extracción de la fecha
  int splitT = formattedDate.indexOf("T");                   
  dayStamp = formattedDate.substring(0, splitT);

  //Extracción de la hora
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);

   /******* Concatenación de datos en las variables cadena de caracteres de acuerdo a la estructura de la base de datos *******/
  //Estas variables cadena de tipo String reciben el número de la planta, la fecha, la hora, el nombre de la variable y
  //la variable de lectura que almacena el dato
  Luz_c=("2, '"+dayStamp+"', '"+timeStamp+"', 'Luz', "+ Luz);
  Humedad_c=("2, '"+dayStamp+"', '"+timeStamp+"', 'Humedad', "+ Humedad);
  Temperatura_c=("2, '"+dayStamp+"', '"+timeStamp+"', 'Temperatura', "+ Temperatura);
  CO_c=("2, '"+dayStamp+"', '"+timeStamp+"', 'Monoxido de carbono', "+ CO);
 
  // Longitud de las variables String (con un caracter extra null que indica terminación)
  int L_len = Luz_c.length() + 1; 
  int H_len = Humedad_c.length() + 1; 
  int T_len = Temperatura_c.length() + 1; 
  int CO_len = CO_c.length() + 1; 

  // Declaración de arreglos tipo char[] con una longitud dinámica
  char L_array[L_len];
  char H_array[H_len];
  char T_array[T_len];
  char CO_array[CO_len];

  //Conversión de las cadenas de tipo String a char[]
  Luz_c.toCharArray(L_array, L_len);
  Humedad_c.toCharArray(H_array, H_len);
  Temperatura_c.toCharArray(T_array, T_len);
  CO_c.toCharArray(CO_array, CO_len);

  //Impresión de los arreglos tipo char[] en el puerto serial
  Serial.println(L_array);
  Serial.println(H_array);
  Serial.println(T_array);
  Serial.println(CO_array);

  //Publicación de los arreglos de datos en las variables de tipo "Adafruit_MQTT_Publish" definidas previamente
  Luz_B1.publish(L_array);
  delay(1);
  Humedad_B1.publish(H_array);
  delay(1);
  Temperatura_B1.publish(T_array);
  delay(1);
  CO_B1.publish(CO_array);
  delay(1);
  Luz_B2.publish(Luz);
  delay(1);
  Humedad_B2.publish(Humedad);
  delay(1);
  Temperatura_B2.publish(Temperatura);
  delay(1);
  CO_B2.publish(CO);
  delay(1);
  Lluvia_B2.publish(Lluvia);
  delay(10000);
}

/*================================== CONECTAR A MQTT ========================================*/
// Función para conectar y reconectar según sea necesario al servidor MQTT.
void MQTT_connect() {
  int8_t ret;
  //Si el MQTT está conectado, termina la función
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 10;
  while ((ret = mqtt.connect()) != 0) { //connect devolverá 0 para conectado, en otro caso connack devolverá el código de error
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 1 second...");
       mqtt.disconnect();
       delay(1000);
       retries--;
       if (retries == 0)
         Serial.println("No Conectado");
  }
  Serial.println("MQTT Connected!");
}
