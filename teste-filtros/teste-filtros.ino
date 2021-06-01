#include "input.hpp"
#include "FiltroPassaBaixa.hpp"
#include "FiltroPassaAlta.hpp"


void setup()
{
    Serial.begin(57600);
    entrada::setup();
}



FiltroPassaAlta filtro_1 (0.8);
FiltroPassaBaixa filtro_2 (0.3);
FiltroPassaAlta filtro_3 (0.8);
FiltroPassaBaixa filtro_4 (0.3);

void loop()
{
    while (1)
    {

        float sinal_de_entrada = entrada::read();
        
                
        float sinal_saida1 = filtro_1.update(filtro_2.update(sinal_de_entrada));
        float sinal_saida2 = filtro_4.update(filtro_3.update(sinal_de_entrada));
               
                        
        
        Serial.print(sinal_de_entrada); Serial.print('\t');
        Serial.print(sinal_saida1); Serial.print('\t');
        Serial.print(sinal_saida2); Serial.print('\t');
        Serial.print('\n');
                             
        
        _delay_ms(100);
    }
    
}
