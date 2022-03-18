#include "DHT.h"
//here we use 14 of ESP32 to read data
#define DHTPIN 22
//our sensor is DHT11 type
#define DHTTYPE DHT11
//create an instance of DHT sensor
DHT dht(DHTPIN, DHTTYPE);
 
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define WLAN_SSID   "WIFICASA"
#define WLAN_PASS   "52184716ca"


// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);


// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;
String Humedadp;
String Temperaturap;
String Luzp;



//MQTT broker settings 
#define HOST        "aulal.org"
#define PORT        1883
#define USERNAME    "mqtt"
#define PASSWORD    "mqtt"

//time out loop count
const int timeout = 200;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, HOST, PORT, USERNAME, PASSWORD);
Adafruit_MQTT_Publish Humedad = Adafruit_MQTT_Publish(&mqtt, "/G1/Humedad1");
Adafruit_MQTT_Publish Luz = Adafruit_MQTT_Publish(&mqtt, "/G1/Luz1");
Adafruit_MQTT_Publish Temperatura = Adafruit_MQTT_Publish(&mqtt, "/G1/Temperatura1");
Adafruit_MQTT_Publish Humedad2 = Adafruit_MQTT_Publish(&mqtt, "/G1/Humedad2");
Adafruit_MQTT_Publish Luz2 = Adafruit_MQTT_Publish(&mqtt, "/G1/Luz2");
Adafruit_MQTT_Publish Temperatura2 = Adafruit_MQTT_Publish(&mqtt, "/G1/Temperatura2");

void MQTT_connect();


void setup() { 
  delay(1); 
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
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(-18000);
  MQTT_connect();
  //init_MPU_sensor();
  dht.begin();
}

void loop() 
{
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();
  //Serial.println(formattedDate);
  
  //int x = random(0,10);
  //int y = random(0,10);
  //int z = random(0,10);
  
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
     Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Extract date and time
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  //Serial.print("DATE: ");
  //Serial.println(dayStamp);
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  //Serial.print("HOUR: ");
  //Serial.println(timeStamp);

  Humedadp=("1, '"+dayStamp+"', '"+timeStamp+"', 'Humedad', "+ (-1*((analogRead(36)/4)-1024)));
  Luzp=("1, '"+dayStamp+"', '"+timeStamp+"', 'Luz', "+ analogRead(39));
  Temperaturap=("1, '"+dayStamp+"', '"+timeStamp+"', 'Temperatura', "+t);
 
  // Define 
  //String str = "This is my string"; 

  // Length (with one extra character for the null terminator)
  int H_len = Humedadp.length() + 1; 
  int T_len = Temperaturap.length() + 1; 
  int L_len = Luzp.length() + 1; 

  // Prepare the character array (the buffer) 
  char H_array[H_len];
  char T_array[T_len];
  char L_array[L_len];

  Humedadp.toCharArray(H_array, H_len);
  Temperaturap.toCharArray(T_array, T_len);
  Luzp.toCharArray(L_array, L_len);
  
  Humedad.publish(H_array);
  delay(1);
  Luz.publish(L_array);
  //delay(1);
  //acelera_z.publish(z);
  delay(1);
  Temperatura.publish(T_array);
  //Serial.print(h);
  delay(1);
  Temperatura2.publish(t);
  delay(1);
  Humedad2.publish(-1*((analogRead(36)/4)-1024));
  delay(1);
  Luz2.publish(analogRead(39));
  //Humedad2.publish(h);
  //Serial.println(t);
  delay(30000);
  
  //Serial.print("1, '"+dayStamp+"', '"+timeStamp+"', 'Temperatura', "+t);
  Serial.println(T_array);
  Serial.println(L_array);
  Serial.println(H_array);

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
