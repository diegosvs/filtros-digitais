
/*
equação no tempo discreto para filtro passa-baixa
y_i = a * x_i + (1 - a) * y_i-1
a = ((2 * pi * tempo de amostragem * frequencia de corte)/
    ((2 * pi * tempo de amostragem * frequencia de corte)+1))

y_i   = saida do filtro
y_i-1 = estado anterior da saida
x_i   = sinal de entrada
a     = constante de atenuação 0 =< a =< 1
*/


namespace DSP
{

class FiltroPassaBaixa
{

    private:
        const float k;
        float estado_filtro;

    public:
        FiltroPassaBaixa(const float &_constante_de_atenuacao) : 
        k (_constante_de_atenuacao) {}
        
        
        FiltroPassaBaixa(const float &_frequencia_de_corte, const float &_tempo_de_amostragem) : 
        k ( ( 6.283f * _tempo_de_amostragem * _frequencia_de_corte) / 
           (( 6.283f * _tempo_de_amostragem * _frequencia_de_corte) + 1.f )) {}
               
    
    float update(const float &_sinal_para_filtragem)
    {
        //this->estado_filtro = this->estado_filtro * this->k + (1.f - this->k )* _sinal_para_filtragem;
        
        this->estado_filtro = _sinal_para_filtragem * this->k + (1.f - k )* this->estado_filtro;

        return this->estado_filtro;        
    }

};

}

