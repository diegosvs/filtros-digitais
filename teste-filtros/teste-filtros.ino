#include "input.hpp"

void setup()
{
    Serial.begin(57600);
    entrada::setup();
}

float filter_state = 0.f;
const float k = 0.64 ;


void loop()
{
    while (1)
    {
        /*  passa baixa, com a constante que multiplica filter state determina o corte, 
        sendo que quanto maior a constante, menor será a banda de passagem*/                       
        filter_state = (1.f - k) * entrada::read() + k * filter_state; 

        Serial.println(filter_state);
        
        _delay_ms(100);
    }
    
}
