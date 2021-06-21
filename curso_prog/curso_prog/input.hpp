//---------------------------------------------------------------
//      ___   ____  ______        __                _       
//     / _ | / / / / __/ /__ ____/ /________  ___  (_)______
//    / __ |/ / / / _// / -_) __/ __/ __/ _ \/ _ \/ / __(_-<
//   /_/ |_/_/_/ /___/_/\__/\__/\__/_/  \___/_//_/_/\__/___/
//                                           Grégory F. Gusberti
// --------------------------------------------------------------

/*
	Curso Introdução à DSP e conceitos de C++
	Faça o curso exclusivo: https://space.hotmart.com/allelectronics
	
	Módulo: input
	Autor:  Grégory 

	Este módulo possibilita a configuração do ADC
	e a leitura de um valor analógico no pino SIGN
*/
namespace input
{
	const uint8_t VCC = A0;
	const uint8_t GND = A4;

	const uint8_t SIGN = A2;

	void setup()
	{
		pinMode(VCC, OUTPUT);
		digitalWrite(VCC, HIGH);

		pinMode(GND, OUTPUT);
		digitalWrite(GND, LOW);

		pinMode(SIGN, INPUT);
	}

	inline float read()
	{
		return analogRead(SIGN);
	}
}