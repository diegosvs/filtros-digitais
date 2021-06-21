//---------------------------------------------------------------
//      ___   ____  ______        __                _       
//     / _ | / / / / __/ /__ ____/ /________  ___  (_)______
//    / __ |/ / / / _// / -_) __/ __/ __/ _ \/ _ \/ / __(_-<
//   /_/ |_/_/_/ /___/_/\__/\__/\__/_/  \___/_//_/_/\__/___/
//                                           Grégory F. Gusberti
// --------------------------------------------------------------

// 	Curso Introdução à DSP e conceitos de C++
//	Faça o curso exclusivo: https://space.hotmart.com/allelectronics

#include <stddef.h>

namespace pwm_dac
{
	void setup()
	{
		TCCR2A  = (1 << WGM20);   // Fast PWM 8 bits 
		TCCR2A |= (1 << WGM21);

		TCCR2A |= (1 << COM2A1); // clear on compare match

		TCCR2B  = (1 << CS20);   // clk / 1

		OCR2A = 127;      // bits superiores

		DDRB |= (1 << 4); // portas como saída
	}

	inline void set_output(const float& value)
	{
		int16_t integer_value = value * 0xFF;

		if (integer_value > 0xFF) integer_value = 0xFF;
		if (integer_value < 0x00) integer_value = 0x00;

		OCR2A = (uint8_t)integer_value;
	}

	inline void set_word(const uint8_t value)
	{
		OCR2A = value;
	}
}