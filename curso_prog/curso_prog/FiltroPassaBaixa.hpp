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

	Módulo: FiltroPassaBaixa
	Autor:  Grégory F. Gusberti 

	Filtro passa-baixa IIR de primeira ordem
*/

namespace DSP
{
	class FiltroPassaBaixa
	{
		private:
			const float k;
			float state;
		
		public:
			FiltroPassaBaixa(const float &_k)
			: k(_k)
			{
				
			}

			FiltroPassaBaixa(const float &fc, const float &dt)
			: k(1.f / ((6.283f * dt * fc) + 1.f))
			{

			}

			float update(const float &input)
			{		
				this->state = this->k * this->state + (1.f - this->k) * input;
				
				return this->state;
			}
	};
}