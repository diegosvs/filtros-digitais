
#include "FiltroPassaBaixa.hpp"
#include "Temperatura.hpp"
#include "Umidade.hpp"


void setup()
{   
    const int A0;
    const int A5;
    pinMode(A0, INPUT);
    pinMode(A5, INPUT);   
    Serial.begin(57600);
    //config::terminais();
}

Temperatura temperatura1(5, 10000);
Umidade umidade1(5);
DSP::FiltroPassaBaixa filtro_t(0.3, 0.05);
DSP::FiltroPassaBaixa filtro_u(0.3, 0.05);

void loop()
{
    while (1)
    {   
        const float temp_ad = filtro_t.update(analogRead(A0));
        const float umid_ad = filtro_u.update(analogRead(A5));

        Serial.print(temperatura1.lerTemperatura(temp_ad));
        Serial.print('\t');
        Serial.print(umidade1.lerUmidade(umid_ad));
        //Serial.println(config::lerUmidade());
        Serial.print('\n');

        _delay_ms(50);
    }
    
}
