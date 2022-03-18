#include "DHT.h"                        //Se agrega la librearia del sensor DHT11
#define DHTPIN 15                       //Se define el PIN del ESP32 al que va el sensor DHT11, de acuerdo al esquemático de la Wiki
#define DHTTYPE DHT22                  //Se define el tipo del sensor (DHT11)
DHT dht(DHTPIN, DHTTYPE);               //Se define una instanciaResultados  para el sensor DHT11
 
#include "Adafruit_MQTT.h"              //Se agregan las librerias para la comunicación MQTT 
#include "Adafruit_MQTT_Client.h"
#include <WiFi.h>                       //Se agrega la librearia para la comunicación WiFi
#include <NTPClient.h>
#include <WiFiUdp.h>                    //Se agrega libreria WiFi para adquisición de fecha y hora

#define WLAN_SSID   "C137"           //Nombre de la red WiFi
#define WLAN_PASS   "2128dali"         //Contraseña de la red WiFi

WiFiUDP ntpUDP;                         //Se define cliente para obtener fecha y hora
NTPClient timeClient(ntpUDP);

// Variables para almacenar la información de cada sensor
String formattedDate;
String dayStamp;
String timeStamp;
String Humedadp;
String Temperaturap;
String Luzp;
String COp;

//Configuración del receptor de MQTT  
#define HOST        "agronet.ddns.net"   //Dominio del host
#define PORT        1883                //Puerto donde está instalada el MQTT
#define USERNAME    "esp32"             //Usuario MQTT
#define PASSWORD    "esp32"             //Contraseña de MQTT

const int timeout = 200;                //Conteo de tiempo de espera para conexión MQTT

//Configuración variables enviadas por MQTT
WiFiClient client;               
Adafruit_MQTT_Client mqtt(&client, HOST, PORT, USERNAME, PASSWORD);
Adafruit_MQTT_Publish Temperatura_B1 = Adafruit_MQTT_Publish(&mqtt, "/G1/Temperatura_P3_B1");
Adafruit_MQTT_Publish Humedad_B1 = Adafruit_MQTT_Publish(&mqtt, "/G1/Humedad_P3_B1");
Adafruit_MQTT_Publish Luz_B1 = Adafruit_MQTT_Publish(&mqtt, "/G1/Luz_P3_B1");
Adafruit_MQTT_Publish CO_B1 = Adafruit_MQTT_Publish(&mqtt, "/G1/CO_P3_B1");
Adafruit_MQTT_Publish Temperatura_B2 = Adafruit_MQTT_Publish(&mqtt, "/G1/Temperatura_P3_B2");
Adafruit_MQTT_Publish Humedad_B2 = Adafruit_MQTT_Publish(&mqtt, "/G1/Humedad_P3_B2");
Adafruit_MQTT_Publish Luz_B2 = Adafruit_MQTT_Publish(&mqtt, "/G1/Luz_P3_B2");
Adafruit_MQTT_Publish CO_B2 = Adafruit_MQTT_Publish(&mqtt, "/G1/CO_P3_B2");

void MQTT_connect();                    //Ejecuta la función para conectarse a MQTT

int aux_lec = 0 ;

//Inicialización
void setup() { 
  delay(1); 
  WiFi.mode(WIFI_STA);   
  Serial.begin(115200);                                              //Configuración del puerto serial (Baudios)                                           
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);                                  //Inicialización de la conexión WiFi
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
  
  timeClient.begin();                                               //Inicialización del cliente para obtener fecha y hora 
  timeClient.setTimeOffset(-18000);                                 //Selección zona horaria. GTM -5 = -18000 para Colombia
  MQTT_connect();                                                   //Inicialización de la conexión MQTT
  dht.begin();                                                      //Inicialización del sensor DHT11
}

void loop() 
{
  while(!timeClient.update())                                       //Actualización de fecha y hora
  {
    timeClient.forceUpdate();                                        
  }  
  formattedDate = timeClient.getFormattedDate();
  
  float t = dht.readTemperature();                                  //Lectura de la temperatura del DHT11 en Celsius (por defecto)
  float sensorValue = 15.6;//analogRead(22);
  
  if (isnan(t)) {                                                   //Verifiación de cualquier falla de lecura y descononexión del sensor DHT11, para reconectar
     Serial.println("Failed to read from DHT sensor!");
    return;
  }

  int splitT = formattedDate.indexOf("T");                          //Extract date and time
  dayStamp = formattedDate.substring(0, splitT);

  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  
  aux_lec = analogRead(34)-2000; //(analogRead(34)-2000);//((800 - (analogRead(34)-2000))/400)*100;
  //Serial.println( analogRead(34) );
  Humedadp=("3, '"+dayStamp+"', '"+timeStamp+"', 'Humedad', "+ aux_lec);
  Luzp=("3, '"+dayStamp+"', '"+timeStamp+"', 'Luz', "+ analogRead(39));
  Temperaturap=("3, '"+dayStamp+"', '"+timeStamp+"', 'Temperatura', "+t);
  COp=("3, '"+dayStamp+"', '"+timeStamp+"', 'Monoxido de carbono', "+sensorValue);
 
  // Length (with one extra character for the null terminator)
  int L_len = Luzp.length() + 1; 
  int H_len = Humedadp.length() + 1; 
  int T_len = Temperaturap.length() + 1; 
  int CO_len = COp.length() + 1; 

  // Prepare the character array (the buffer) 
  char L_array[L_len];
  char H_array[H_len];
  char T_array[T_len];
  char CO_array[CO_len];

  Luzp.toCharArray(L_array, L_len);
  Humedadp.toCharArray(H_array, H_len);
  Temperaturap.toCharArray(T_array, T_len);
  COp.toCharArray(CO_array, CO_len);

  Serial.println(L_array);
  Serial.println(H_array);
  Serial.println(T_array);
  Serial.println(CO_array);
  delay(500);

  
  Luz_B1.publish(L_array);
  delay(1);
  Humedad_B1.publish(H_array);
  delay(1);
  Temperatura_B1.publish(T_array);
  delay(1);
  CO_B1.publish(CO_array);
  delay(1);
  Luz_B2.publish(analogRead(39));
  delay(1);
  Humedad_B2.publish(aux_lec);
  delay(1);
  Temperatura_B2.publish(t);
  delay(1);
  CO_B2.publish(sensorValue);
  delay(10000);

  

}

void MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 10;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
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
