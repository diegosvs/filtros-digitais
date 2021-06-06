#include "input.hpp"
#include "FiltroPassaBaixa.hpp"
#include "FiltroPassaAlta.hpp"



void setup()
{
    Serial.begin(57600);
    entrada::setup();
}

DSP::FiltroPassaAlta     filtro_1 = DSP::FiltroPassaAlta (5, 0.05);
DSP::FiltroPassaBaixa    filtro_2 = DSP::FiltroPassaBaixa (6, 0.05);
//DSP::FiltroPassaBaixa     filtro_3 = DSP::FiltroPassaBaixa (1, 0.02);


void loop()
{
    //filtro_a.setConstante(0.6);


    while (1)
    {

        float sinal_de_entrada = entrada::read();
        

        float sinal_saida = filtro_1.update(sinal_de_entrada);
        float sinal_saida1 = filtro_2.update(sinal_saida);
        //float sinal_saida2 = filtro_2.update(filtro_1.update(sinal_de_entrada));
      
                        
        
        Serial.print(sinal_de_entrada); Serial.print('\t');
        //Serial.print(sinal_saida); Serial.print('\t');
        Serial.print(sinal_saida1); Serial.print('\t');
        //Serial.print(sinal_saida2); Serial.print('\t');
        Serial.print('\n');
                             
        
        _delay_ms(50);
    }
    
}
