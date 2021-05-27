#include "input.hpp"

void setup()
{
    Serial.begin(9600);
    entrada::setup();
}

void loop()
{
    while (1)
    {
        Serial.println(entrada::read());
        
        _delay_ms(50);
    }
    
}
