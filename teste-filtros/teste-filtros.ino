
#include "FiltroPassaBaixa.hpp"
#include "Temperatura.hpp"
#include "Umidade.hpp"
#include "config.hpp"
#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>
#include <PubSubClient.h>
//#include <DHT.h>
//#include "WiFi.h"      //ESP32
#include <ESP8266WiFi.h> //ESP8266

#define BAUDE_RATE 9600

#define TOKEN "lmmthg005"
#define TEMPO_DADO_BROKER 0.1 // tempo em minutos para aquisição no broker da thingsboard

#define WIFI_AP "IPT-WiFi"
#define WIFI_PASSWORD "the@trum"

#define FILTRO 0.08               //filtro em Hz para condicionamento dos sinais
#define AMOSTRAGEM_DO_FILTRO 0.05 //amostragem do filtro em segundos

#define OFFSET_HIGROMETRO -20
#define OFFSET_TERMOMETRO 0
#define RESISTOR_SERIE 9820
#define TENSAO_ALIMENTACAO 3.3
#define RESOLUCAO_CONDICIONADOR 10 // resolucao do conversor em bits


TH::Temperatura temperatura1(RESOLUCAO_CONDICIONADOR, RESISTOR_SERIE,OFFSET_TERMOMETRO);                // argumentos (resolução AD, resistor serie do NTC)
TH::Umidade umidade1(RESOLUCAO_CONDICIONADOR, TENSAO_ALIMENTACAO, OFFSET_HIGROMETRO); // argumentos (resolução AD, tensao de alimentacao, offset)
DSP::FiltroPassaBaixa filtro_temperatura(FILTRO, AMOSTRAGEM_DO_FILTRO);               // argumentos (Hz, tempo de amostragem)
DSP::FiltroPassaBaixa filtro_umidade(FILTRO, AMOSTRAGEM_DO_FILTRO);

WiFiClient wifiClient;


PubSubClient client(wifiClient);

char thingsboardServer[] = "iothmlsice.ipt.br";

int status = WL_IDLE_STATUS;

unsigned long lastSend;
unsigned long comutar;

void setup()
{
    Serial.begin(BAUDE_RATE);
    config::setup();

    delay(10);
    InitWiFi();
    client.setServer(thingsboardServer, 1883);
    lastSend = 0;
    comutar = 0;
}

void loop()
{

    if (!client.connected())
    {
        reconnect();
    }

    if (millis() - comutar > (AMOSTRAGEM_DO_FILTRO * 1000))
    { // Update and send only after 1 seconds
        chaveamento();
        comutar = millis();
    }


    if (millis() - lastSend > (TEMPO_DADO_BROKER * 60000))
    { // Update and send only after 1 seconds
        getAndSendTemperatureAndHumidityData();
        lastSend = millis();
    }

    
    client.loop();
}

void chaveamento()
{
    config::ativaTemperatura();
    const float t = filtro_temperatura.update(temperatura1.lerTemperatura(config::sinalAD()));
    config::ativaUmidade();
    const float h = filtro_umidade.update(umidade1.lerUmidade(config::sinalAD()));
}

void getAndSendTemperatureAndHumidityData()
{
    config::ativaUmidade();
    const float h = filtro_umidade.update(umidade1.lerUmidade(config::sinalAD()));
    
    config::ativaTemperatura();
    const float t = filtro_temperatura.update(temperatura1.lerTemperatura(config::sinalAD()));

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Serial.print("Humidity: ");
    // Serial.print(h);
    // Serial.print(" %\t");
    // Serial.print("Temperature: ");
    // Serial.print(t);
    // Serial.print(" *C ");

    String temperature = String(t);
    String humidity = String(h);

    // // Just debug messages
    // Serial.print("Sending temperature and humidity : [");
    // Serial.print(temperature);
    // Serial.print(",");
    // Serial.print(humidity);
    // Serial.print("] -> ");

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
            //digitalWrite(LED_BUILTIN, LOW);
        }

        else
        {
            Serial.print("[FAILED] [ rc = ");
            Serial.print(client.state());
            Serial.println(" : retrying in 5 seconds]");
            // Wait 5 seconds before retrying
            //digitalWrite(LED_BUILTIN, LOW);
            delay(5000);
        }
    }
}
