/*
equação no tempo discreto para filtro passa-alta
y_i = a * ( y_i-1 + (x_i - x_i-1))
a = (1 / (2 * pi * tempo de amostragem * frequencia de corte +1))

y_i     = saida do filtro
y_i-1   = estado anterior da saida
x_i     = sinal de entrada
x_i-1   = sinal anterior de entrada
a       = constante de atenuação 0 =< a =< 1
*/


namespace DSP
{

class FiltroPassaAlta
{
private:
    const float k;
    float estado_do_filtro;
    float _der=0;

public:
    FiltroPassaAlta(const float &_constante_filtragem) : 
    k (_constante_filtragem) {}    
    
    FiltroPassaAlta(const float &_frequencia_de_corte, const float &_tempo_de_amostragem) : 
    k (1.f / (6.283f * _tempo_de_amostragem * _frequencia_de_corte + 1.f)) {}

    float update(const float &sinal_para_filtragem)
    {
        
        this->estado_do_filtro = this->k * (this->estado_do_filtro + (sinal_para_filtragem - this->_der));
        
        this->_der = sinal_para_filtragem;
        
        return this-> estado_do_filtro;
    }


};

}
