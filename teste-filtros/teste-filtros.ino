#include "input.hpp"
#include "FiltroPassaBaixas.hpp"


void setup()
{
    Serial.begin(57600);
    entrada::setup();
}



FiltroPassaBaixas filtro_A (0.1);
FiltroPassaBaixas filtro_B (0.7);
FiltroPassaBaixas filtro_C (0.95);


//float _der = 0;


void loop()
{
    while (1)
    {

        float sinal_de_entrada = entrada::read();
        
        float sinal_filtro_a = filtro_A.update(sinal_de_entrada);
        float sinal_filtro_a2 = filtro_B.update(sinal_filtro_a);
        float sinal_filtro_a3 = filtro_C.update(sinal_filtro_a2);
        
                        
        
        Serial.print(sinal_de_entrada); Serial.print('\t');
        Serial.print(sinal_filtro_a); Serial.print('\t');
        Serial.print(sinal_filtro_a2); Serial.print('\t');
        Serial.print(sinal_filtro_a3); Serial.print('\n');
        
        //Serial.print(sinal_filtro_saida); Serial.print('\n');
        
        
        _delay_ms(100);
    }
    
}
