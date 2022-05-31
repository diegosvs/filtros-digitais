
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


#define WIFI_AP "IPT-IoT"
#define WIFI_PASSWORD "r@cion@l"

//DHT
#define DHTPIN 4
#define DHTTYPE DHT22


WiFiClient wifiClient;

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

PubSubClient client(wifiClient);

char thingsboardServer[] = "iothmlsice.ipt.br"; // endereço do thingsboard

int status = WL_IDLE_STATUS;

unsigned long lastSend;

void setup()
{
    Serial.begin(BAUDE_RATE);
    dht.begin();
    delay(10);
    InitWiFi();   
    client.setServer(thingsboardServer, 1883);
    lastSend = 0;
    
    
}

void loop()
{

/*---------------------------------------------------------------*/
                    /*conecta ao broker */
                    
    if (!client.connected())
    {
        reconnect();
    }

/*---------------------------------------------------------------*/

   
    if (millis() - lastSend > (TEMPO_DADO_BROKER * 60000)) // conta minutos para envio de payload
    { 
        getAndSendTemperatureAndHumidityData();
        lastSend = millis();
    }

    
    client.loop();
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
    while (!client.connected())
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
        if (client.connect("ESP8266 Device", TOKEN, NULL))
        {
            Serial.println("[DONE]");
            digitalWrite(LED_BUILTIN, LOW);
            getAndSendTemperatureAndHumidityData(); // envia um payload ao broker assim que dispositivo é ligado
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
