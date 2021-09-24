
#include "FiltroPassaBaixa.hpp"
#include "Temperatura.hpp"
#include "Umidade.hpp"
#include "config.hpp"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ArduinoHttpClient.h>
#include "WiFi.h"      //ESP32
//#include <ESP8266WiFi.h> //ESP8266
#include <ThingsBoard.h>

#define HOSTIP "10.66.0.63:8080"
#define TOKEN "WpskTXZMUuk7UDRodXl7"




TH::Temperatura       temperatura1(12, 17920); // argumentos (resolução AD, resistor serie do NTC)
TH::Umidade           umidade1(12, 3.3, 500);  // argumentos (resolução AD, tensao de alimentacao, offset)
DSP::FiltroPassaBaixa filtro_temperatura(0.1, 0.05); // argumentos (Hz, tempo de amostragem)
DSP::FiltroPassaBaixa filtro_umidade(0.1, 0.05);

const char *ssid_wifi = "IPT-WiFi-Novo";     /*  INSERIR O NOME DA REDE WIFI QUE O DISPOSITIVO SERÁ CONECTADO */
const char *password_wifi = "germ@nium";


WiFiClient espClient;  
ThingsBoard tb(espClient) ;

void init_wifi(void);
void (*funcReset)()=0;
void connect_wifi(void);  
void reconnect();
void verify_wifi_connection(void);

void init_wifi(void) 
{
    delay(10);
    Serial.println("------WI-FI -----");
    Serial.print("Tentando se conectar a rede wi-fi ");
    Serial.println(ssid_wifi);
    Serial.println("Aguardando conexao");    
    connect_wifi();
}

void reconnect() {
  // Loop until we're reconnected
  
  while (!tb.connected()) {
    Serial.print("Connecting to ThingsBoard node ...");
    // Attempt to connect (clientId, username, password)
    if ( tb.connect(HOSTIP, TOKEN) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED]" );
      Serial.println( " : retrying in 5 seconds" );
      // Wait 5 seconds before retrying
      delay( 600 );
    }
  }
}

/* Funcao: conexao a uma rede wi-fi */
void connect_wifi(void) 
  {
    if (WiFi.status() == WL_CONNECTED)
        return;
        
    WiFi.disconnect();
    WiFi.begin(ssid_wifi, password_wifi);
    //WiFi.config(ip, gateway, subnet); //configuração para IP fixo
    
    while (WiFi.status() != WL_CONNECTED) 
    {
        //digitalWrite(LED_BUILTIN, LOW);
         // delay(100);
          //digitalWrite(LED_BUILTIN, HIGH);
          //delay(400);
    }
  
      Serial.println();
      Serial.print("Conectado a rede wi-fi: ");
      Serial.println(ssid_wifi);
      Serial.println(WiFi.SSID());
      Serial.print("IP: ");
      Serial.println(WiFi.localIP());
      Serial.println(WiFi.gatewayIP());
      Serial.println(WiFi.subnetMask());
      Serial.println(WiFi.macAddress());
  }

  void verify_wifi_connection(void)
{
    connect_wifi(); 
}

void setup()
{      
    config::setup();
    Serial.begin(9600);
    init_wifi();       
}


void loop()
{
    while (1)
    {   
        verify_wifi_connection();

        if ( !tb.connected() ) {reconnect();}
        
        //const float temperatura_ad = config::sinalADTemperatura();        
        //const float conversor_temperatura = temperatura1.lerTemperatura(temperatura_ad);
        //const float dado_temperatura = filtro_temperatura.update(conversor_temperatura);
        
       
        //const float umidade_ad = config::sinalADUmidade();        
        //const float conversor_umidade = umidade1.lerUmidade(umidade_ad);
        //const float dado_umidade = filtro_umidade.update(conversor_umidade);

        // Serial.print(temperatura_ad);
        // Serial.print('\t'); 
        // Serial.print(conversor_temperatura,1);
        // Serial.print('\t');
        // Serial.print(dado_temperatura,1);
        // Serial.print('\t');  

        //Serial.print(umidade_ad);
        //Serial.print('\t');
        //Serial.print(conversor_umidade,1);
        //Serial.print('\t');
        //Serial.print(dado_umidade,1);
        //Serial.print('\n');
        tb.sendTelemetryFloat("temperature", 500);
        
        
        
        tb.loop();
        delay(500);
    }
    
}
