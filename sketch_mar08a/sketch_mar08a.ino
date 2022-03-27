#include <HTTPClient.h>
#include<WiFi.h>;

const char* ssid="ESTACION LUNAR KND";
const char* pass="4E4f204d414D4553";//el bueno
//const String host="https://api.openweathermap.org/data/2.5/weather?zip=78000,mx&lang=es&units=metric&appid=49410277f3568265c037ce59a3a520b7";//bueno
const String host="https://reqbin.com/echo/get/json";//pruevas
//const String host="https://api.openweathermap.org/data/2.5/weather?q=san%20luis%20Potosi&units=metric&appid=49410277f3568265c037ce59a3a520b7";
//const String host="https://api.openweathermap.org/data/2.5/weather?lat=35&lon=139&appid=49410277f3568265c037ce59a3a520b7";

//const String privateKey="49410277f3568265c037ce59a3a520b7";

IPAddress ip(192, 168, 0, 99);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);


void setup() {
  Serial.begin(115200);
  coneccion();
  Serial.println("\nCONECTADO");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("gateway:");
  Serial.println(WiFi.gatewayIP());
  Serial.print("dns:");
  //Serial.println(WiFi.dnsIp(1));
  
  
}

void loop() {
  
  if((WiFi.status()==WL_CONNECTED)){
    Serial.print("\nConectado:");
    Serial.print(WiFi.localIP());

    HTTPClient http;
    Serial.println("\n"+host);
    http.begin(host);//url
    int httpCode=http.GET();//tipo de peticion
    
    if(httpCode>0){
      String data=http.getString();
      Serial.println(httpCode);
      Serial.println(data);
    }
    else{
      Serial.println("error HTTP ");
      
    }
    http.end();//liberar recursos
  }
  else{
    Serial.println("Desconectado");
  }
  delay(2000);
  
}

void coneccion(){
  //WiFi.config(staticIP, gateway, subnet, dns, dns)  ;
  WiFi.config(ip, dns, gateway, subnet);
  //WiFi.setDNS(dns);
  
  WiFi.begin(ssid,pass);
  
  
  Serial.println("Conectando wifi");
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
}
