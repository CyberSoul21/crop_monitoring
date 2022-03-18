#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <WiFi.h>
#include "DHT.h"

//Definimos el typo de sensor
#define DHTTYPE DHT11

//Usamos el pun 15 del ESP32 para leer datos
#define DHTPIN 15

//create an instance of DHT sensor
Adafruit_BMP085 bmp;
 
#define WLAN_SSID   "Nombre de la red WiFi"
#define WLAN_PASS   "Contraseña de la red"

//MQTT broker settings 
#define HOST        "aulal.org"
#define PORT        1883
#define USERNAME    "mqtt"
#define PASSWORD    "mqtt"

DHT dht(DHTPIN, DHTTYPE);

//time out loop count
const int timeout = 200;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, HOST, PORT, USERNAME, PASSWORD);
Adafruit_MQTT_Publish Temperatura = Adafruit_MQTT_Publish(&mqtt, "/G1/Diana/Temperatura");
Adafruit_MQTT_Publish HumedadA = Adafruit_MQTT_Publish(&mqtt, "/G1/Diana/HumedadA");
Adafruit_MQTT_Publish Presion = Adafruit_MQTT_Publish(&mqtt, "/G1/Diana/Presion");

void MQTT_connect();
//void init_MPU_sensor();
//void MPU_sensor();

void setup() { 
  delay(1000); 
  //call begin to start DHT sensor
  dht.begin();
  //call begin to start BMP sensor
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085/BMP180 sensor, check wiring!");
  while (1) {}
  }
  WiFi.mode(WIFI_STA);  
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

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

  MQTT_connect();
  //init_MPU_sensor();
}

void loop() 
{
//use the functions which are supplied by library.
float h = dht.readHumidity();
// Read temperature as Celsius (the default)
float t = dht.readTemperature();
// Read presion as Pascals
float p = bmp.readPressure();
// Check if any reads failed and exit early (to try again).
if (isnan(h) || isnan(t)|| isnan(p)) {
Serial.println("Failed to read from sensors!");
return;
}
  
  Temperatura.publish(t);
  delay(1);
  HumedadA.publish(h);
  delay(1);
  Presion.publish(p);
  delay(1);
  //Serial.print(ax_d); Serial.print("\t");Serial.print(ay_d); Serial.print("\t");Serial.print(az_d); Serial.println("\t");
  //MPU_sensor();
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
