class Umidade
{
private:
    const int terminal;
    const float tensao_alimentacao;
    const float max;
    const float min;
    const float fator;

public:
    Umidade(const int &_terminal,
            const float &_tensao_alimentacao) :

                                                terminal(_terminal),
                                                tensao_alimentacao(_tensao_alimentacao / 1023.0f),
                                                max(3.198f / _tensao_alimentacao / 1023.0f),
                                                min(0.826f / tensao_alimentacao / 1023.0f)
    {
    }

    float lerUmidade()
    {
        /*
        5V / 1023bits= 0,0032V/bit
        0%    ur --> 0,826V --> 258 bits
        75,3% ur --> 3,198V --> 999 bits 
        666 - 172 = 741 divisões
        741 / 75,3 = 9,84 --> 0,1% ur
        */

        float max = (3.198f / tensao_alimentacao);
        float min = (0.826f / tensao_alimentacao);

        float fator = (max - min) / 75.3f;

        float leitura_ad_umidade = analogRead(terminal);

        float valor_umidade = (leitura_ad_umidade - max) / fator;
        if (leitura_ad_umidade < min)
        {
            return valor_umidade = 0.0f;
        }

        else if (leitura_ad_umidade >= (max + min))
        {
            return valor_umidade = 100.0f;
        }

        else
        {
            return valor_umidade;
            //return leitura_ad_umidade;
        }
    }
};
