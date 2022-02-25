
#include "FiltroPassaBaixa.hpp"
#include "Temperatura.hpp"
#include "Umidade.hpp"
#include "config.hpp"

#define FILTRO  0.08 // Hz
#define OFFSET_TEMP 15.7
#define OFFSET_UMID 7 
#define AMOSTRAGEM  0.05 // s  
#define RESOLUCAO_AD 10
#define RESISTOR_SERIE 9820
#define TENSAO_ALIMENTACAO 3.3


TH::Temperatura       temperatura1(RESOLUCAO_AD, RESISTOR_SERIE, OFFSET_TEMP); // argumentos (resolução AD, resistor serie ao NTC, offset)
TH::Umidade           umidade1(RESOLUCAO_AD, TENSAO_ALIMENTACAO, OFFSET_UMID); // argumentos (resolução AD, tensao de alimentacao, offset)
DSP::FiltroPassaBaixa filtro_temperatura(FILTRO, AMOSTRAGEM); // argumentos (Hz, tempo de amostragem)
DSP::FiltroPassaBaixa filtro_umidade(FILTRO, AMOSTRAGEM);


void setup()
{       
    Serial.begin(57600);
    config::setup();
}


void loop()
{    
    while (1)
    {   
        /**/
        config::ativaTemperatura();
        const float temperatura_ad = config::sinalAD();
        const float conversor_temperatura = temperatura1.lerTemperatura(temperatura_ad);
        const float dado_temperatura = filtro_temperatura.update(conversor_temperatura);
        
        config::ativaUmidade();
        const float umidade_ad = config::sinalAD();
        const float conversor_umidade = umidade1.lerUmidade(umidade_ad);
        const float dado_umidade = filtro_umidade.update(conversor_umidade);
        

        //Serial.print(temperatura_ad,1);
        //Serial.print('\t');  
        Serial.print(conversor_temperatura,1);
        Serial.print('\t');
        Serial.print(dado_temperatura,1);
        Serial.print('\t');        
        
        //Serial.print(umidade_ad,1);
        //Serial.print('\t');  
        Serial.print(conversor_umidade,1);
        Serial.print('\t');
        Serial.print(dado_umidade,1);
        Serial.print('\n');

        delay(AMOSTRAGEM*1000);
    }
    
}
