#include <SoftwareSerial.h>

SoftwareSerial serial1 (6, 7); // RX, TX //LCD
SoftwareSerial serial2 (4, 5); // RX, TX //FPGA

String data = "0";

void setup() {

  Serial.begin(9600);
  // put your setup code here, to run once:
  serial1.begin(9600);//LCD
  serial2.begin(9600);//FPGA
}

void loop() {
  // put your main code here, to run repeatedly:
  while (serial2.available())
  {
    data = serial2.readStringUntil('\n');
    //data = serial1.readString();
    Serial.println(data);
    serial1.print(data);     
  }
  while (Serial.available())
  {
    data = Serial.readStringUntil('\n');
    //data = Serial.readString();
    Serial.println(data);
    
    if(data == "baud11")
    {
      serial1.print("t0.txt=\"115200\"");
      serial1.write(0xff);
      serial1.write(0xff);
      serial1.write(0xff);
/*
      serial1.print("baud=115200");  Cambio de la tasa de transmisión
      serial1.write(0xff);
      serial1.write(0xff);
      serial1.write(0xff);
*/  
    }
    if(data == "baud3")
    {
      Serial.print("t0.txt=\"38400\"");
      
      serial2.print("t0.txt=\"38400\"");
      serial2.write(0xff);
      serial2.write(0xff);
      serial2.write(0xff); 
    }
    if(data == "s")
    {
      Serial.print("t0.txt=\"fpga\"ÿÿÿ");
      serial1.print("t0.txt=\"fpga\"ÿÿÿ");

    }    
    /*
    serial1.print("t0.txt=\"Wilson\"");   
    serial1.write(0xff);
    serial1.write(0xff);
    serial1.write(0xff);    
 */
  }
  

}
