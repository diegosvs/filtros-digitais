
#include "FiltroPassaBaixa.hpp"
#include "Temperatura.hpp"
#include "Umidade.hpp"


void setup()
{   
    const int A0;
    const int A5;
    pinMode(A0, INPUT);
    pinMode(A5, INPUT);
    //pinMode(D4,OUTPUT);
    //pinMode(D5,OUTPUT);
    Serial.begin(57600);
    //config::terminais();
}

TH::Temperatura       temperatura1(1023, 5, 10000); // argumentos (resolução AD, tensao de alimentacao, resistor serie do NTC)
TH::Umidade           umidade1(1023, 5, 169); // argumentos (resolução AD, tensao de alimentacao, offset)
DSP::FiltroPassaBaixa filtro_t(0.3, 0.05); // argumentos (Hz, tempo de amostragem)
DSP::FiltroPassaBaixa filtro_u(0.3, 0.05);

void loop()
{
    while (1)
    {   
        const float temp_ad = filtro_t.update(analogRead(A0));
        const float umid_ad = filtro_u.update(analogRead(A5));

        Serial.print(temperatura1.lerTemperatura(temp_ad),1);
        Serial.print('\t');
        Serial.print(umidade1.lerUmidade(umid_ad),1);
        //Serial.println(config::lerUmidade());
        Serial.print('\n');

        _delay_ms(50);
    }
    
}
