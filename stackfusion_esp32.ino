#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "starwars";
const char* password = "Malhotras21";

unsigned long last_time = 0;
unsigned long timer_delay = 10000;

String json_array;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting to WIFI...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("First set of readings will appear after 10 seconds");
}

void loop() {
  
  if ((millis() - last_time) > timer_delay) {
  
    if(WiFi.status()== WL_CONNECTED){
      String server = "https://fastag-internal.parkzap.com/account/mockable_test/";
      
      json_array = GET_Request(server.c_str());
      Serial.println(json_array);
      JSONVar my_obj = JSON.parse(json_array);
  
      if (JSON.typeof(my_obj) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.print("JSON object = ");
      Serial.println(my_obj);
      Serial.print("1: ");
      Serial.println(my_obj[0]);
      Serial.print("2: ");
      Serial.println(json_array[0]);
      // Serial.println(my_obj["main"]["temp"]);
      // Serial.print("Pressure: ");
      // Serial.println(my_obj["main"]["pressure"]);
      // Serial.print("Humidity: ");
      // Serial.println(my_obj["main"]["humidity"]);
      // Serial.print("Wind Speed: ");
      // Serial.println(my_obj["wind"]["speed"]);
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    last_time = millis();
  }
}

String GET_Request(const char* server) {
  HTTPClient http;    
  http.begin(server);
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  return payload;
}