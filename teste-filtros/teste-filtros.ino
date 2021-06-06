#include "config.hpp"
#include "FiltroPassaAlta.hpp"
#include "FiltroPassaBaixa.hpp"


void setup()
{
    Serial.begin(57600);
    
    config::terminais();
}

void loop()
{
    while (1)
    {
       Serial.print(config::lerTemperatura());
       Serial.print('\t');
       Serial.println(config::lerUmidade());
        
        _delay_ms(100);
    }
    
}
