#include "config.hpp"
#include "FiltroPassaBaixa.hpp"
#include "Temperatura.hpp"
#include "Umidade.hpp"


void setup()
{   
    const int A0;
    const int A5;
    pinMode(A0, INPUT);
    pinMode(A5, INPUT);   
    Serial.begin(57600);
    //config::terminais();
}

Temperatura temperatura1(A0, 5, 18000);
Umidade umidade1(A5, 5);

void loop()
{
    while (1)
    {   
        //float leitura_ad_temperatura = config::lerTemperatura();

        //Serial.print(leitura_ad_temperatura);

        Serial.print(temperatura1.lerTemperatura());
        Serial.print('\t');
        Serial.print(umidade1.lerUmidade());
        //Serial.println(config::lerUmidade());
        Serial.print('\n');

        _delay_ms(100);
    }
    
}
