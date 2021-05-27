#include "input.hpp"

void setup()
{
    Serial.begin(57600);
    
    entrada::setup();
}

void loop()
{
    while (1)
    {
       Serial.print(entrada::readTemperatura());
       Serial.print('\t');
       Serial.println(entrada::readUmidade());
        
        _delay_ms(100);
    }
    
}
