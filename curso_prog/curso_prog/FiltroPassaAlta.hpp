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

	Módulo: FiltroPassaAlta
	Autor:  Grégory F. Gusberti

	Filtro passa-alta IIR de primeira ordem
*/

namespace DSP
{
	class FiltroPassaAlta
	{
		private:
			const float k;
			float state;
			float _der;

		public:
			FiltroPassaAlta(const float &_k)
			: k(_k)
			{
				
			}

			FiltroPassaAlta(const float &fc, const float &dt)
			: k(1.f / ((6.283f * fc * dt) + 1.f))
			{

			}

			float update(const float &input)
			{
				this->state = this->k * (this->state + (input - this->_der));
				this->_der  = input;

				return this->state;
			}
	};
}
