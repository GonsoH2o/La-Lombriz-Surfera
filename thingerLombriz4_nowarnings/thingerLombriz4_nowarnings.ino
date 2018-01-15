#include <ESP8266WiFi.h>       //Librería de conexión WiFi del módulo ESP8266
#include <ThingerESP8266.h>    //Librería de la plataforma thinger.io
#include "DHT.h"               //Librería de los sensores DHT11, DHT22, etc. 
 
// Parámetros del conexión con thinger.io
#define usuario "thinger_user"
#define device_Id "thinger_device"
#define device_credentials "thinger_device_pass"
 
ThingerESP8266 thing(usuario, device_Id, device_credentials);
 
// Parámetros de conexión WiFi
const char WiFi_ssid[]="ssid_name";            //Nombre de red
const char WiFi_password[]="wifi_password";  //Clave de red
//const char WiFi_ssid[]="******";            //Nombre de red
//const char WiFi_password[]="*******";  //Clave de red
// Parámetros del DHT 
#define DHTPIN D4     //Pin de conexión - GPIO02
#define DHTTYPE DHT11   //Modelo
 
DHT dht(DHTPIN, DHTTYPE);
  int valor_salida ;
  void setup() {
  
  // Inicialización del DHT11
  dht.begin();
  pinMode(A0, INPUT);
  
  
 
  // Inicialización de la WiFi para comunicarse con la API
  thing.add_wifi(WiFi_ssid, WiFi_password);
 
  // Inicialización de la lectura de datos desde la API
  thing["Sense8"] >> [](pson& out){
    out["Temperatura"] = dht.readTemperature();
    out["Humedad"] = dht.readHumidity();
    };
 
  thing["Higo8"] >> [](pson& out){
    valor_salida = analogRead(A0);
    valor_salida = map(valor_salida, 960, 0, 0, 100);
    out["Humedad en suelo"] = analogRead(A0); //valor_salida;
    };
  
  }


  
unsigned long lastCheck = 0;
void loop() {


  thing.handle();
  unsigned long currentTs = millis();
 
 /* La parte de Avisos da error y finalizala conexión con Thinger.io -- Revisar */
 //   if(currentTs-lastCheck>=60*60*1000){
 // if(dht.readTemperature()<5){
 //           thing.call_endpoint("temp_low");
 //           delay(3600000);
 //       }
 //   }
 // if(currentTs-lastCheck>=60*60*1000){
 // if(dht.readTemperature()>25){
 //           thing.call_endpoint("temp_high");
 //           delay(3600000);
 //       }
 //   }  
//  if(currentTs-lastCheck>=60*60*1000){
//  if(dht.readHumidity()<70){
//            thing.call_endpoint("hum_low");
//            delay(3600000);
//        }
//    }
 
    
}
