#include "input.hpp"

void setup()
{
    Serial.begin(57600);
    entrada::setup();
}

float filter_state = 0.f;

const float k = 0.3;

float _der = 0;


void loop()
{
    while (1)
    {
                              
        /* filtro passa alta, fator k determina a taxa de decaimento até 0, quanto
        menor k, mais rápido é o decaimento e maior é a passagem para altas frequencias e menos é
        a passagem para baixas frequencias*/
        
        const float tmp = entrada::read();
                
        filter_state = k * (filter_state + (tmp - _der)); 

        _der = tmp; 

        Serial.println(filter_state);
        
        _delay_ms(100);
    }
    
}
