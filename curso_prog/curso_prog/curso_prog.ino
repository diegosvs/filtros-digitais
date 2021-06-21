//---------------------------------------------------------------
//      ___   ____  ______        __                _       
//     / _ | / / / / __/ /__ ____/ /________  ___  (_)______
//    / __ |/ / / / _// / -_) __/ __/ __/ _ \/ _ \/ / __(_-<
//   /_/ |_/_/_/ /___/_/\__/\__/\__/_/  \___/_//_/_/\__/___/
//                                           Grégory F. Gusberti
// --------------------------------------------------------------

//	Curso Introdução à DSP e conceitos de C++
//	Faça o curso exclusivo: https://space.hotmart.com/allelectronics

#include "input.hpp"
#include "FiltroPassaBaixa.hpp"
#include "FiltroPassaAlta.hpp"

#include "pwm_dac.hpp"

#include "TimerOne.h"

// período de amostragem 2.5ms
// taxa de amostragem de 400Hz
const float dt = 0.0025;

void dsp();

void setup()
{
	Serial.begin(57600);

	pwm_dac::setup();
	input::setup();

	Timer1.initialize(dt * 1e6);

	Timer1.attachInterrupt(dsp);
}

// resposta desejada do filtro --------------------
//
//          ##########################
//        ## |                      | ##
//     ###   |                      |   ### 
//   ###     |                      |     ###
//  ##       |                      |       ##
//##         |                      |         ##
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//          6Hz                    15Hz         
// corte do                           corte do
// passa altas                        passa baixas
//-------------------------------------------------

DSP::FiltroPassaBaixa filtro_A(15.5, dt);
DSP::FiltroPassaBaixa filtro_B(15,   dt);

DSP::FiltroPassaAlta  filtro_C(6,   dt);
DSP::FiltroPassaAlta  filtro_D(6.5, dt);

void dsp()
{
	const float input  = input::read();
	
	// passa baixa de segunda ordem 
	const float interm = filtro_B.update(filtro_A.update(input));

	// passa alta de primeira
	const float output = filtro_D.update(filtro_C.update(interm));

	pwm_dac::set_output(0.5f + output / 512.f);
}

void loop()
{
	while(1)
	{

	}
}