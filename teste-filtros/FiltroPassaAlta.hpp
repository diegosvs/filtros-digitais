class FiltroPassaAlta
{
private:
    float k;
    float estado_do_filtro;
    float _der=0;

public:
    FiltroPassaAlta(const float &constante_filtragem)
    {
        this-> k = constante_filtragem;
    }

    float update(const float &sinal_para_filtragem)
    {
        this->estado_do_filtro = this->k * (this->estado_do_filtro+ (sinal_para_filtragem-this->_der));
        this->_der = sinal_para_filtragem;
        
        return this-> estado_do_filtro;
    }


};
