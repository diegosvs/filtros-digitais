#include "input.hpp"
#include "FiltroPassaBaixa.hpp"
#include "FiltroPassaAlta.hpp"
#include "TimerOne.h" //incluir biblioteca na ide do arduino

void dsp();
float rational_tanh(const float &x);

const float dt = 50000.f; // tempo de amostragem em microsegundos, estabelecer referencia em Hz para amostragem
float oscilador = 1.f; // variavel para teste de oscilador baseado em filtro passa alta

DSP::FiltroPassaAlta     filtro_1 = DSP::FiltroPassaAlta (5, dt);
DSP::FiltroPassaBaixa    filtro_2 = DSP::FiltroPassaBaixa (6, dt);
//DSP::FiltroPassaBaixa     filtro_3 = DSP::FiltroPassaBaixa (1, 0.02);


void setup()
{
    Serial.begin(57600);
    entrada::setup();
    Timer1.initialize(dt); //biblioteca utiliza argumentos em microsegundos
    Timer1.attachInterrupt(dsp);
}

float rational_tanh(const float &x)
{
    if(x<3.f)
        return -1.f;
    else if (x>3.f)
        return 1.f;
    else
        return x * ( 27.f + x * x ) / ( 27.f + 9.f * x * x );    
}

void dsp()
{

        oscilador = filtro_1.update(oscilador);
        oscilador = 1.2f * oscilador; //ganho do sinal de entrada
        oscilador = rational_tanh(oscilador); // clipagem do sinal segundo funcao tangente
        Serial.println(oscilador);

        /*
        float sinal_de_entrada = entrada::read();
        float sinal_saida = filtro_1.update(sinal_de_entrada);
        float sinal_saida1 = filtro_2.update(sinal_saida);
        */
              
        //float sinal_saida2 = filtro_2.update(filtro_1.update(sinal_de_entrada));
        //Serial.print(sinal_de_entrada); Serial.print('\t');
        //Serial.print(sinal_saida); Serial.print('\t');
        //Serial.print(sinal_saida1); Serial.print('\t');
        //Serial.print(sinal_saida2); Serial.print('\t');
        //Serial.print('\n');
                             
}


void loop()
{
    
    while (1)
    {}
    
}
