/*Cliente estación metereológica. 
 * Bot Telegram para la consulta de los datos.
 * Palabras admitidas - Datos  Muestra la lectura de los sensores en formato texto
 *                      Link Muestra un link hacia las gráficas de Grafana instalado en la pi.

 * */

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////////////////////===== Librerías =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include <Arduino.h>
#include <ESP8266WiFi.h>  //Librería de conexión WiFi del módulo ESP8266
#include <ESP8266HTTPClient.h>  //Librería de conexión cliente del módulo ESP8266
#include <ThingerESP8266.h> //Librería de la plataforma thinger.io
#include <Wire.h>              // Librería para el sensor BME280
#include <SPI.h>               // Librería para el sensor BME280
#include <Adafruit_Sensor.h>  // Librería para el sensor BME280
#include <Adafruit_BME280.h>  // Librería para el sensor BME280
#include <ArduinoOTA.h> //Librería necesaria para el uso de OTA
#include "ESP8266_Utils_OTA.hpp"  //Configuración para uso de OTA
#include "CTBot.h"  //Librería para el bot de Telegram
#include "config.h" 

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
////////////////////////////////////===== Fin librerías =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*===================================================================================================*/

/*//////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////////////////===== Variables locales =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

float tempint;
float humeint;
int rssiInt;

/*//////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
////////////////////////////////===== Fin variables locales =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*===================================================================================================*/

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
////////////////////////////////===== Parámetros Thinger.io =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

//============================== Datos Thinger.io

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

#define _DEBUG_

//============================== Value httpRequest Thinger.io
String lastBucketValue;

/*-----------------VARIABLES DE LOS DATOS OBTENIDOS DESDE THINGER.IO--------------------*/
float tempout;
float humeout;
int rssiOUT;
float presion;
float altitud;
float dViento;
int fViento;
String punto_Cardinal;
float uV;
float lLuvia1h;
float lLuvia24h;
float lumi;
float p_Rocio;

/*---------IMPORTANTE no poner la "s" en "http" ------------------*/
String link = "TU_LINK_DE_THINGER.IO";  //De donde sacaras en JSON

/*-------------------FUNCIÓN PARA SACAR LAS VARIABLES DE THINGER.IO-------------------*/
String httpRequest_THINGERio (String link) 
{
  String payload;
  if (WiFi.status() == WL_CONNECTED) //Check Wifi connection status
  {  
    HTTPClient http;  //Declare an object of class HTTPClient
    http.begin (link);  //Petición específica destino
    int httpCode = http.GET();

    Serial.print ("Código HTTP: ");
    Serial.println (httpCode);

    if (httpCode > 0 ) 
    {  //Check the returning code. Thinger.io codes. 200 = ok, 401 = No authorized, 404 = No found.
      payload = http.getString(); //Get the request response payload
      //Serial.println ("El valor de payload es "); //comentar una vez comprobado que interpreta bien los datos
      //Serial.println (payload); //comentar una vez comprobado que interpreta bien los datos
    } else if (httpCode < 0) {  //If the returning code is less than 0, there is an error, them
      Serial.println ("ERROR payload");
    }
    http.end(); //Close connection
  }
  return payload;
}
/*----------------------------------FIN FUNCIÓN----------------------------------*/

/*-------------------FUNCIÓN PARA SACAR LAS VARIABLES DE THINGER.IO-------------------*/
float varExtract (String varToExtract, String payload) 
{
  int Start = payload.indexOf (varToExtract) + varToExtract.length() + 2; //Indicamos el inicio donde se encuentra el valor del sensor.
  /*----------https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/length/ ----------------*/
  //Serial.println("El valor de Start es: "); //comentar una vez comprobado que interpreta bien los datos
  //Serial.println (Start);   //comentar una vez comprobado que interpreta bien los datos
  int End = payload.indexOf (",", Start); //Indicamos donde acaba nuestro  valor del sensor
  //Serial.println("El valor de End es: "); //comentar una vez comprobado que interpreta bien los datos
  //Serial.println (End); //comentar una vez comprobado que interpreta bien los datos
  if (End < 0) {  //Last variable doesn't have "," at the end, have a "]"
    End = payload.indexOf ("}");
  }
  String stringVar = payload.substring (Start, End);  //Obtiene el valor con todos los decimales, 16.7784938493202 p.e.
  //Serial.println("El valor de stringVar es :"); //comentar una vez comprobado que interpreta bien los datos
  //Serial.println(stringVar);  //comentar una vez comprobado que interpreta bien los datos
  float var = stringVar.toFloat();  //Nos quedamos con solo 2 decimales.
  //Serial.println("El valor de var es: "); //comentar una vez comprobado que interpreta bien los datos
  //Serial.println(var);  //comentar una vez comprobado que interpreta bien los datos
  return var;
}
/*----------------------------------FIN FUNCIÓN----------------------------------*/

/*-------------------FUNCIÓN PARA SACAR LA VARIABLE String DE THINGER.IO-------------------*/
String varCaracterExtract (String varToExtract, String payload) 
{
  int Start = payload.indexOf (varToExtract) + varToExtract.length() + 2; //Indicamos el inicio donde se encuentra el valor del sensor.
  /*----------https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/length/ ----------------*/
  //Serial.println("El valor de Start es: "); //comentar una vez comprobado que interpreta bien los datos
  //Serial.println (Start);   //comentar una vez comprobado que interpreta bien los datos
  int End = payload.indexOf (",", Start); //Indicamos donde acaba nuestro  valor del sensor
  //Serial.println("El valor de End es: "); //comentar una vez comprobado que interpreta bien los datos
  //Serial.println (End); //comentar una vez comprobado que interpreta bien los datos
  if (End < 0) {  //Last variable doesn't have "," at the end, have a "]"
    End = payload.indexOf ("}");
  }
  String stringVar = payload.substring (Start, End);  //Obtiene el valor con todos los decimales, 16.7784938493202 p.e.
  //Serial.println("El valor de stringVar es :"); //comentar una vez comprobado que interpreta bien los datos
  //Serial.println(stringVar);  //comentar una vez comprobado que interpreta bien los datos
  return stringVar;
}
/*----------------------------------FIN FUNCIÓN----------------------------------*/

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////////////===== Fin parámetros Thinger.io =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*===================================================================================================*/

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
///////////////////////////////////===== Parámetros Wifi =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*-----------Datos conexión Wifi-----------*/
const char* host = "TU_IP_SERVIDOR";  // IP servidor
const int   port = 80;            // Puerto servidor

/*----------FUNCIÓN PARA LA CONEXIÓN A LA RED WIFI-----------*/
void configWifi () 
{
  Serial.print ("Conectando con ");
  Serial.println (ssid);

//============================== Wifi conexion
  WiFi.mode (WIFI_STA); //Configuración en modo cliente
  WiFi.begin (ssid, password); //Iniciamos la conexión WiFi

  //WiFi.config (staticIP, gateway, subnet);  //Configuramos la conexión

  while (WiFi.status() != WL_CONNECTED) { //Mientras no estemos conectados
    delay(500); //Cada medio segundo
    Serial.print (".");   //Imprimimos un "." por el monitor serie.
  }
  Serial.println ("");
  Serial.print ("Conectado a la red ");
  Serial.println (ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////===== Fin parámetros Wifi =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*===================================================================================================*/

Adafruit_BME280 bme; // BME280 conectado por I2C

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////////////////===== Parámetros timer =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

//============================== Timer
unsigned long ultimaConsulta = 0;
unsigned long tiempoConsulta = 60000;

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
////////////////////////////===== Parámetros envío datos a BD =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*---FUNCIÓN PARA EL ENVÍO DE LAS LECTURAS DE LOS SENSORES A LA BASE DE DATOS---*/
void httprequest_DATA_BASE () 
{ 
  /*------------LAS VARIABLES LOCALES------------*/
  tempint = bme.readTemperature();
  humeint = bme.readHumidity();
  rssiInt = WiFi.RSSI();

  WiFiClient client;

  if (!client.connect(host, port)) 
  {
    Serial.println("Fallo al conectar");
    return;
  }
  /*---------------------------------Así se muestra en el navegador---------------------------------*/
  /* //http://IP_SERVIDOR/BASE_DE_DATOS/index.php?tempint=7&humeint=9&tempout=1&humeout=70&presion=1025.15&lumi=160 */

  String url = "/BASE_DE_DATOS/index.php?"; //Construimos la URL datos_Estacion/index.php?temp=[La tª del sensor]&hume=[la humedad del sensor]
  url += "&tempint=";
  url += tempint; //mostrará la temperatura después de &tempint=
  url += "&humeint="; //añadimos lo que falta a la URl(ha de coincidir con las variables creadas en el archivo php)
  url += humeint; //mostrará la humedad después de &humeint=
  url += "&rssiInt="; //ha de coincidir con las variables creadas en el archivo php - No  confundir con las variables de la base de datos.
  url += rssiInt;
  url += "&tempout=";
  url += tempout;
  url += "&humeout=";
  url += humeout;
  url += "&p_Rocio=";
  url += p_Rocio;
  url += "&rssiOUT="; 
  url += rssiOUT;
  url += "&presion="; //ha de coincidir con las variables creadas en el archivo php - No  confundir con las variables de la base de datos.
  url += presion; //mostrará la presión 
  url += "&altitud=";
  url += altitud;
  url += "&dViento=";
  url += dViento;
  url += "&fViento=";
  url += fViento;
  url += "&punto_Cardinal=";
  url += punto_Cardinal;
  url += "&uV=";
  url += uV; 
  url += "&lLuvia1h=";
  url += lLuvia1h; 
  url += "&lLuvia24h=";
  url += lLuvia24h; 
  url += "&lumi=";
  url += lumi;

  //============================== Enviamos petición al servidor
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
    
      return;
    }
  }

  //============================== Leemos la respuesta del servidor
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
   
  }
}

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//////////////////////////===== Fin parámetros envío datos a BD =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*===================================================================================================*/

void timer () 
{
  if (millis() < ultimaConsulta)  //Comprobar si se ha dado la vuelta
  {  
    ultimaConsulta = millis();  //Asignar un nuevo valor
    
  }
  if ((millis() - ultimaConsulta) > tiempoConsulta) 
  {
    ultimaConsulta = millis();  //Marca de tiempo
    
    /* -----------GUARDAMOS LAS LECTURAS DE LOS SENSORES DESDE THINGER.IO EN VARIABLES-----------*/
    lastBucketValue = httpRequest_THINGERio (link);
    tempout = varExtract ("Temperatura", lastBucketValue);
    humeout = varExtract ("Humedad", lastBucketValue);
    rssiOUT = varExtract ("RSSI out", lastBucketValue);
    presion = varExtract ("Presión", lastBucketValue);
    altitud = varExtract ("Altitud aproximada", lastBucketValue);
    lumi = varExtract ("Luminosidad", lastBucketValue);
    uV = varExtract ("Indice UV", lastBucketValue);
    p_Rocio = varExtract ("Punto de rocio", lastBucketValue);
    dViento = varExtract ("Ángulo", lastBucketValue);
    fViento = varExtract ("Viento-(V)", lastBucketValue);
    punto_Cardinal = varCaracterExtract ("Cardinal", lastBucketValue);
    lLuvia1h = varExtract ("Lluvia1h", lastBucketValue);
    lLuvia24h = varExtract ("Lluvia24h", lastBucketValue);
    
    /*------Comentar una vez comprobado que interpreta bien los datos------*/

    /* Serial.print ("Temperatura exterior: ");
       Serial.print (tempout);
       Serial.println ("ºC");*/
    /*----------------------------FIN COMENTAR----------------------------*/

    /*------Comentar una vez comprobado que interpreta bien los datos------*/

    /* Serial.print ("Humedad exterior: ");
       Serial.print (humeout);
       Serial.println ("%");*/
    /*----------------------------FIN COMENTAR----------------------------*/

    /*------Comentar una vez comprobado que interpreta bien los datos------*/

    /* Serial.print ("Señal RSSI out: ");
       Serial.print (rssiOUT);
       Serial.println ("dBm");*/
    /*----------------------------FIN COMENTAR----------------------------*/
    
    /*------Comentar una vez comprobado que interpreta bien los datos------*/

    /* Serial.print ("Presión: ");
       Serial.print (presion);
       Serial.println ("hPa"); */
    /*----------------------------FIN COMENTAR----------------------------*/

   /*------Comentar una vez comprobado que interpreta bien los datos------*/

    /* Serial.print ("Altitud aproximada: ");
       Serial.print (altitud);
       Serial.println ("m");*/
    /*----------------------------FIN COMENTAR----------------------------*/
    
   /*------Comentar una vez comprobado que interpreta bien los datos------*/

    /* Serial.print ("La dirección del viento es: ");
       Serial.print (dViento);
       Serial.print ("º");*/
    /*----------------------------FIN COMENTAR----------------------------*/

    /*------Comentar una vez comprobado que interpreta bien los datos------*/
    /* Serial.print ("La fuerza del viento es: ");
       Serial.print (fViento);
       Serial.println ("Km/h"); */
    /*----------------------------FIN COMENTAR----------------------------*/

    /*------Comentar una vez comprobado que interpreta bien los datos------*/
    /* Serial.print ("El punto cardinal es: ");
       Serial.println (punto_Cardinal);*/
    /*----------------------------FIN COMENTAR----------------------------*/

    /*------Comentar una vez comprobado que interpreta bien los datos------*/
    /*  Serial.print ("El índice Uv es: ");
       Serial.print (uV); 
       Serial.println ("mW/cm^2");  */
    /*----------------------------FIN COMENTAR----------------------------*/

    /*------Comentar una vez comprobado que interpreta bien los datos------*/
    /*  Serial.print ("El punto de rocío es: ");
        Serial.print (p_Rocio);
        Serial.println ("ºC");  */
    /*----------------------------FIN COMENTAR----------------------------*/
    
    /*------Comentar una vez comprobado que interpreta bien los datos------*/
    /* Serial.print ("la cantidad de lLuvia1h es: ");
       Serial.print (lLuvia1h);
       Serial.println ("mm2"); */
    /*----------------------------FIN COMENTAR----------------------------*/

    /*------Comentar una vez comprobado que interpreta bien los datos------*/
    /* Serial.print ("la cantidad de lLuvia24h es: ");
       Serial.print (lLuvia24h);
       Serial.println ("mm2"); */
    /*----------------------------FIN COMENTAR----------------------------*/
    
    /*------Comentar una vez comprobado que interpreta bien los datos------*/

    /* Serial.print ("Luminosidad: ");
       Serial.print (lumi);
       Serial.println ("lux"); */
    /*----------------------------FIN COMENTAR----------------------------*/
    /*leer_Sensores_Local (); //Mostramos la lectura de los sensores local por el puerto serie*/

    httprequest_DATA_BASE() ; //Enviamos los datos de los sensores mediante una dirección web que guardará un php
    
  }
}

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
////////////////////////////////===== Fin parámetros timer =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*===================================================================================================*/

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////===== Muestra datos sensor local =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

void leer_Sensores_Local () 
{
  //============================== Mostrar los datos de los sensores por el puerto serie.
  Serial.print ("Temperatura local: ");
  Serial.print (bme.readTemperature());
  Serial.println (" ºC");
  Serial.print ("Humedad local: ");
  Serial.print (bme.readHumidity());
  Serial.println ("%");
  Serial.print ("Temp out: ");
  Serial.println (tempout);
  Serial.print ("Humedad out: ");
  Serial.println (humeout);
  Serial.print ("RSSI local: ");
  Serial.print (WiFi.RSSI());
  Serial.println ("dBm");
}

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
///////////////////////////===== Fin muestra datos sensor local =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

/*===================================================================================================*/

/*///////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
////////////////////////////////////===== Bot Telegram =====\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
/////////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

CTBot myBot;

void setup() 
{
  Serial.begin (9600);  //Iniciamos el monitor serie
  configWifi(); //Conectamos a la red Wifi.
  thing.add_wifi (ssid, password);  //Conectamos a Thinger.IO

  unsigned status;
  //============================== default settings
  status = bme.begin(0x76);
  //============================== You can also pass in a Wire library object like &Wire2
  //============================== status = bme.begin(0x76, &Wire2)
  if (!status) {
    Serial.println("¡¡No se encuentra el sensor BME280, comprueba conexiones, dirección y la ID del sensor!!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probablemente la dirección está mal o el sensor es un BMP 180 o BMP 085\n");
    Serial.print("   ID of 0x56-0x58 representa un BMP 280,\n");
    Serial.print("        ID of 0x60 representa un BME 280.\n");
    Serial.print("        ID of 0x61 representa un BME 680.\n");
    while (1) delay(10);
  }
  
  /*----------------------------------Bot Telegram----------------------------------*/

  Serial.println("Inicializando el bot de Telegram...");
  //myBot.wifiConnect(ssid, password);  //Conectamos el ESP8266 a la red wifi.
  myBot.setTelegramToken(token);  //Establecemos el token del bot de Telegram
 
  if (myBot.testConnection()) //Comprobamos que todo está correcto.
    Serial.println("\ntest Conexión OK");
  else
    Serial.println("\ntest Conexión No OK");

   /*-----------------------------Fin bot Telegram----------------------------------*/ 
    
  InitOTA();  //Ajustes como puerto, password, etc (ESP8266_Utils_OTA.hpp)
}

void loop() 
{
  timer();
  
  TBMessage msg;  //Variable para almacenar los mensajes de Telegram
   
  if (myBot.getNewMessage (msg))  //Si hay mensajes entrantes
                
    String link;
    String info;

    if ((msg.text == "Datos"))
    {
      String todo_Concatenado;
      todo_Concatenado += "Altura:  ";
      todo_Concatenado += "\t\t\t";
      todo_Concatenado += altitud;
      todo_Concatenado += "m";
      todo_Concatenado += "\r\n\r\n";
      todo_Concatenado += "Dirección y velocidad viento:  ";
      todo_Concatenado += dViento;
      todo_Concatenado += " ";
      todo_Concatenado += punto_Cardinal;
      todo_Concatenado += "\t\t\t";
      todo_Concatenado += fViento;
      todo_Concatenado += "km/h";
      todo_Concatenado += "\r\n\r\n";
      todo_Concatenado += "T out:  ";
      todo_Concatenado += tempout;
      todo_Concatenado += "ºC";
      todo_Concatenado += "\r\n";
      todo_Concatenado += "Hume out:  ";
      todo_Concatenado += "\t\t\t";
      todo_Concatenado += humeout;
      todo_Concatenado += "%";
      todo_Concatenado += "\r\n\r\n";
      todo_Concatenado += "T int:  ";
      todo_Concatenado += tempint;
      todo_Concatenado += "ºC";
      todo_Concatenado += "\r\n";
      todo_Concatenado += "Hume int:  ";
      todo_Concatenado += "\t\t\t";
      todo_Concatenado += humeint;
      todo_Concatenado += "%";
      todo_Concatenado += "\r\n\r\n";
      todo_Concatenado += "P. rocío:  ";
      todo_Concatenado += "\t\t\t";
      todo_Concatenado += p_Rocio;
      todo_Concatenado += "ºC";
      todo_Concatenado += "\r\n";
      todo_Concatenado += "Presión:  ";
      todo_Concatenado += "\t\t\t";
      todo_Concatenado += presion;
      todo_Concatenado += "hPa";
      todo_Concatenado += "\r\n";
      todo_Concatenado +="Radiación: ";
      todo_Concatenado += "\t\t\t";
      todo_Concatenado +=  uV;
      todo_Concatenado += "\r\n\r\n";
      todo_Concatenado += "Lluvia 1h:  ";
      todo_Concatenado += lLuvia1h;
      todo_Concatenado += "mm";
      todo_Concatenado += "\r\n";
      todo_Concatenado += "Lluvia 24h:  ";
      todo_Concatenado += lLuvia24h;
      todo_Concatenado += "mm";
      todo_Concatenado += "\r\n\r\n";
      todo_Concatenado += "Luminosidad:  ";
      todo_Concatenado += "\t\t\t";
      todo_Concatenado += lumi;
      todo_Concatenado += "lux";
      todo_Concatenado += "\r\n\r\n";  
      todo_Concatenado += "Rssi: out  ";
      todo_Concatenado += rssiOUT;
      todo_Concatenado += "dBm";
      todo_Concatenado += "\t";
      todo_Concatenado += "int ";
      todo_Concatenado += rssiInt;
      todo_Concatenado += "dBm";

      myBot.sendMessage (msg.sender.id, todo_Concatenado);
    }
    if ((msg.text == "Link"))
    {
      link = "poner tu propio enlace ";  //Enlace gráficas grafana en la pi.
      
      myBot.sendMessage (msg.sender.id, link);
    }
        
  ArduinoOTA.handle();
}