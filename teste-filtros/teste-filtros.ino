#include "input.hpp"
#include "FiltroPassaBaixas.hpp"
#include "FiltroPassaAlta.hpp"


void setup()
{
    Serial.begin(57600);
    entrada::setup();
}



FiltroPassaAlta filtro_A_alta (0.5);
FiltroPassaBaixas filtro_A_baixa (0.6);


void loop()
{
    while (1)
    {

        float sinal_de_entrada = entrada::read();
        
                
        float sinal_saida = filtro_A_alta.update(filtro_A_baixa.update(sinal_de_entrada));
               
                        
        
        Serial.print(sinal_de_entrada); Serial.print('\t');
        Serial.print(sinal_saida); Serial.print('\t');
        Serial.print('\n');
                             
        
        _delay_ms(100);
    }
    
}
