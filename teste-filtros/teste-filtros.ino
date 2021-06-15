
#include "FiltroPassaBaixa.hpp"
#include "Temperatura.hpp"
#include "Umidade.hpp"
    
    const int sinal_t = A0;
    const int sinal_h = A5;
    const int gndh = 8;
    const int gndt = 7;

void setup()
{       
    pinMode(sinal_t, INPUT);
    pinMode(sinal_h, INPUT);
    pinMode(gndh, OUTPUT);
    pinMode(gndt, OUTPUT);
    digitalWrite(gndt, HIGH);
    digitalWrite(gndh, HIGH);
    Serial.begin(57600);
    //config::terminais();
}

TH::Temperatura       temperatura1(1023, 5, 14210); // argumentos (resolução AD, tensao de alimentacao, resistor serie do NTC)
TH::Umidade           umidade1(1023, 5, 250); // argumentos (resolução AD, tensao de alimentacao, offset)
DSP::FiltroPassaBaixa filtro_temperatura(0.025, 0.05); // argumentos (Hz, tempo de amostragem)
DSP::FiltroPassaBaixa filtro_umidade(0.025, 0.05);

void loop()
{
    
    while (1)
    {   
        digitalWrite(gndt, LOW);
        digitalWrite(gndh, HIGH);
        const float temperatura_ad = analogRead(sinal_t);
        const float conversor_temperatura = temperatura1.lerTemperatura(temperatura_ad);
        const float dado_temperatura = filtro_temperatura.update(conversor_temperatura);
        
        digitalWrite(gndh, LOW);
        digitalWrite(gndt, HIGH);
        const float umidade_ad = analogRead(sinal_t);
        const float conversor_umidade = umidade1.lerUmidade(umidade_ad);
        const float dado_umidade = filtro_umidade.update(conversor_umidade);


        Serial.print(dado_temperatura,1);
        Serial.print('\t');        
        //Serial.print(conversor_umidade,1);
        //Serial.print('\t');
        Serial.print(dado_umidade,1);
        Serial.print('\n');

        _delay_ms(20);
    }
    
}
