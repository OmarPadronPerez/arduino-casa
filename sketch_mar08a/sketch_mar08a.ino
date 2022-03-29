#include <NTPClient.h>
#include <HTTPClient.h>
#include<WiFi.h>;

//configuracion de red
const char* ssid="ESTACION LUNAR KND";
const char* pass="4E4f204d414D4553";//el bueno
IPAddress ip(192, 168, 0, 99);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

//clima
const String hostClima="https://api.openweathermap.org/data/2.5/weather?zip=78000,mx&lang=es&units=metric&appid=";//bueno
const String privateKey="49410277f3568265c037ce59a3a520b7";
//const String host="https://reqbin.com/echo/get/json";//sevidor de pruevas
//const String host="https://api.openweathermap.org/data/2.5/weather?q=san%20luis%20Potosi&units=metric&appid=49410277f3568265c037ce59a3a520b7";
//const String host="https://api.openweathermap.org/data/2.5/weather?lat=35&lon=139&appid=49410277f3568265c037ce59a3a520b7";


//fecha y hora
const String hostRelog="";
const long utc=-21600;
String diasLargo[7]={"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
String mesLargo[12]={"Ene","Feb","Mar", "Abr","May", "Jun", "Jul", "Ago", "Sep", "Oct", "Nov","Dic"};
int horas=0;
int minutos=0;
int segundos=0;
int dia=0;
int mes=0;
int anio=0;
int diaSem=0;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utc);



void setup() {
  Serial.begin(115200);
  conexion();
  Serial.println("\nCONECTADO");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("gateway:");
  Serial.println(WiFi.gatewayIP());
  //Serial.print("dns:");
  //Serial.println(WiFi.dnsIp(1));
  
  timeClient.begin();
  
}

void loop() {
  
  if((WiFi.status()==WL_CONNECTED)){
    /*Serial.print("\nConectado:");
    Serial.print(WiFi.localIP());*/
    consultarHora();
      Serial.print("\n");
      Serial.print(horas);
      Serial.print(":");
      Serial.print(minutos);
      Serial.print(":");
      Serial.print(segundos);
      //Serial.println(horas +":"+ minutos +":"+ segundos);
    
    //Serial.println(consultarHora());
    Serial.println("\n"+consClima());
    
  }
  else{
    Serial.println("Desconectado");
  }
  delay(1000);
  
}

boolean consultarHora(){
  //timeClient.update();
  
  if(!timeClient.update()){
    diaSem=timeClient.getDay();
    horas=timeClient.getHours();
    minutos=timeClient.getMinutes();
    segundos=timeClient.getSeconds();
    //la fecha se tiene que calcular
    

    return true;
  }else{
    horas=0;
    minutos=0;
    segundos=0;
    return false;
  }
  
  
}

String consClima(){
  HTTPClient http;
    http.begin(hostClima+privateKey);//url
    int httpCode=http.GET();//tipo de peticion
    String data="error";
    
    if(httpCode>0){
      data=http.getString();
      //Serial.println(httpCode);
      //Serial.println(data);
    }
    http.end();//liberar recursos
    return data;
}

void conexion(){
  //WiFi.config(staticIP, gateway, subnet, dns, dns)  ;
  //WiFi.config(ip, dns, gateway, subnet);//checar
  //WiFi.setDNS(dns);
  
  WiFi.begin(ssid,pass);
  
  
  Serial.println("Conectando wifi");
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
}
