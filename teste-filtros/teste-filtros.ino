#include "input.hpp"
#include "FiltroPassaBaixa.hpp"
#include "FiltroPassaAlta.hpp"


void setup()
{
    Serial.begin(57600);
    entrada::setup();
}



FiltroPassaAlta filtro_1 (0.6);
FiltroPassaAlta filtro_2 (0.6);
FiltroPassaAlta filtro_3 (0.6);
FiltroPassaAlta filtro_4 (0.6);
FiltroPassaAlta filtro_5 (0.6);
FiltroPassaAlta filtro_6 (0.6);

/*
FiltroPassaAlta filtro_1 (0.20);
FiltroPassaAlta filtro_2 (0.30);
FiltroPassaAlta filtro_3 (0.40);
FiltroPassaAlta filtro_4 (0.50);
FiltroPassaAlta filtro_5 (0.66);
FiltroPassaAlta filtro_6 (0.88);
*/


void loop()
{
    while (1)
    {

        float sinal_de_entrada = entrada::read();
        
                
        float sinal_saida1 = filtro_1.update(sinal_de_entrada);
        float sinal_saida2 = filtro_2.update(sinal_de_entrada);
        float sinal_saida3 = filtro_3.update(sinal_de_entrada);
        float sinal_saida4 = filtro_4.update(sinal_de_entrada);
        float sinal_saida5 = filtro_5.update(sinal_de_entrada);
        float sinal_saida6 = filtro_6.update(sinal_de_entrada);

        //float sinal_saida3 = filtro_3.update(filtro_4.update(sinal_de_entrada));
        //float sinal_saida4 = filtro_5.update(filtro_6.update(sinal_de_entrada));
               
                        
        
        //Serial.print(sinal_de_entrada); Serial.print('\t');
        Serial.print(sinal_saida1); Serial.print('\t');
        Serial.print(sinal_saida2); Serial.print('\t');
        Serial.print(sinal_saida3); Serial.print('\t');
        Serial.print(sinal_saida4); Serial.print('\t');
        Serial.print(sinal_saida5); Serial.print('\t');
        Serial.print(sinal_saida6); Serial.print('\t');
        Serial.print('\n');
                             
        
        _delay_ms(100);
    }
    
}
