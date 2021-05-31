

class FiltroPassaBaixa
{

    private:
        float k;
        float estado_filtro;

    public:
        FiltroPassaBaixa(const float &constante_de_atenuacao)
        {
            this->k = constante_de_atenuacao;
        }

    
    
    
    float update(const float &sinal_para_filtragem)
    {
        this->estado_filtro = this->estado_filtro * this->k + (1.f - this->k )* sinal_para_filtragem;

        return this->estado_filtro;
        
    }

};