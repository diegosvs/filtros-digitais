
#include "FiltroPassaBaixa.hpp"
#include "Temperatura.hpp"
#include "Umidade.hpp"
#include "config.hpp"
#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>
#include <PubSubClient.h>
#include <DHT.h>
//#include "WiFi.h"      //ESP32
#include <ESP8266WiFi.h> //ESP8266

#define BAUDE_RATE 9600

#define TOKEN "lmmthg002" // senha do dispositivo cadastrado no thingsboard
#define TEMPO_DADO_BROKER 45 // tempo em minutos para aquisição no broker da thingsboard

#define MQTT_USERNAME  "LMM-TU-002"  // nome do dispositivo cadastrado 
#define MQTT_PASSWORD  ""  // se houver senha cadastrada no broker

#define WIFI_AP "IPT-IoT"
#define WIFI_PASSWORD "r@cion@l"

//DHT
#define DHTPIN 4
#define DHTTYPE DHT22

WiFiClient wifiClient;
WiFiClient nodeClient;

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

PubSubClient client(wifiClient);
PubSubClient mqtt_node(nodeClient);

char thingsboardServer[] = "iothmlsice.ipt.br"; // endereço do thingsboard

char broker_mqtt_node[] = "10.5.39.18"; //inserir endereço do broker local
int broker_port = 1882;  // inserir a porta cadastrada no broker

int status = WL_IDLE_STATUS;

unsigned long lastSend;

void setup()
{
    Serial.begin(BAUDE_RATE);
    dht.begin();
    delay(10);
    InitWiFi();   
    client.setServer(thingsboardServer, 1883);
    mqtt_node.setServer(broker_mqtt_node,broker_port);
    mqtt_node.setCallback(callback);
    lastSend = 0;      
}

void loop()
{

/*---------------------------------------------------------------*/
                    /*conecta ao broker */
                    
    if ((!client.connected()))
    {
        reconnect();
    }

     if ((!mqtt_node.connected()))
    {
        reconnect();
    }

/*---------------------------------------------------------------*/
      
    client.loop();
    mqtt_node.loop();
}


void getAndSendTemperatureAndHumidityData()
{

    float h = dht.readHumidity();

    delay(20);

    float t = dht.readTemperature();
    
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    String temperature = String(t);
    String humidity = String(h);

    // Prepare a JSON payload string
    String payload = "{";
    payload += "\"temperatura\":";
    payload += temperature;
    payload += ",";
    payload += "\"umidade\":";
    payload += humidity;
    payload += "}";

    // Send payload
    char attributes[100];
    payload.toCharArray(attributes, 100);
    client.publish("v1/devices/me/telemetry", attributes);
    Serial.println(attributes);
}

void InitWiFi()
{
    Serial.println("Connecting to AP ...");
    // attempt to connect to WiFi network

    WiFi.begin(WIFI_AP, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        //digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
    Serial.println("Connected to AP");
}

void reconnect()
{
    // Loop until we're reconnected
    while ((!client.connected())||(!mqtt_node.connected()))
    {
        status = WiFi.status();
        if (status != WL_CONNECTED)
        {
            WiFi.begin(WIFI_AP, WIFI_PASSWORD);
            while (WiFi.status() != WL_CONNECTED)
            {
                //digitalWrite(LED_BUILTIN, LOW);
                delay(100);
                
                Serial.print(".");
            }
            Serial.println("Connected to AP");
        }

        Serial.print("Connecting to Thingsboard node ...");
        // Attempt to connect (clientId, username, password)
        if ((client.connect("ESP8266 Device", TOKEN, NULL))&&(mqtt_node.connect("teste", MQTT_USERNAME, MQTT_PASSWORD)))
        {
            Serial.println("[DONE]");
            digitalWrite(LED_BUILTIN, LOW);
            getAndSendTemperatureAndHumidityData(); // envia um payload ao broker assim que dispositivo é ligado
            mqtt_node.subscribe("LEDPLACA"); // topico de estado do led
            mqtt_node.subscribe("datatago"); // topico que grava os dados em arquivo local do broker
            mqtt_node.subscribe("datanode"); // topico para envio de dados para o dashboard 
        }
        

        else
        {
            Serial.print("[FAILED] [ rc = ");
            Serial.print(client.state());
            Serial.println(" : retrying in 5 seconds]");
            // Wait 5 seconds before retrying
            digitalWrite(LED_BUILTIN, LOW);
            delay(5000);
        }
    }
}

/* Funcao: checa os tópicos enviados para o esp8266 para interação com o broker */
 void callback(String topic, byte* payload, unsigned int length) 
  {

    String messageTemp; 
    
    for (int i = 0; i < length; i++) 
      {       
        messageTemp += (char)payload[i];
      }  
  
    //Serial.print(messageTemp);
    //Serial.println();
    //Serial.print(topic);
    //Serial.println();

  /*topico que checa se o botao de teste do dashboard do led interno foi pressionado*/
    if(topic=="LEDPLACA") 
        {  
          if(messageTemp == "ligar" )
            {
              bool ledteste=!ledteste;
              digitalWrite(LED_BUILTIN, ledteste);
            }
            
          else if(messageTemp == "desligar")
            {      
              //digitalWrite(LED_BUILTIN, HIGH);
            }
        }  
  
    /*recebe o topico que aciona a funcao de envio de valores para o broker para que sejam armazenados*/
    else if(topic=="datatago") 
        {  
          if(messageTemp == "send_data_tago" )
            {
              getAndSendTemperatureAndHumidityData();
            }     
        }
  
    /*recebe o topico que aciona a funcao de envio de valores para o dashboard*/
    else if(topic=="datanode") 
        {  
          if(messageTemp == "send_data_node" )
            {
              //send_data_nodered();            
            }     
        }       
  }