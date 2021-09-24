namespace TH
{

    class Umidade
    {
    private:
        const float resolucao_ad;
        const float off_set;
        const float tensao_alimentacao;
        const float fator;

    public:
        Umidade(const float &_resolucao_ad,
                const float &_tensao_alimentacao,
                const float &_off_set) : resolucao_ad(pow(2, _resolucao_ad)),
                                         tensao_alimentacao(_tensao_alimentacao),
                                         off_set(_off_set),
                                         fator((tensao_alimentacao / resolucao_ad) / 0.02079f)
        {
        }

        float lerUmidade(const float &_sinal_ad)
        {
            /*
        5V / 1023bits= 0,0032V/bit
        0%    ur --> 0,826V --> 169 bits
        75,3% ur --> 3,198V --> 633,6 bits 
        666 - 172 = 741 divisões
        741 / 75,3 = 9,84 --> 0,1% ur
        offset - 0.826 V
        slope = 31.483 mV/%RH para 5V
        slope = 20.79 mV/%RH para 3,3V
        (VOUT - zero offset)/slope
        ur = (VOUT - 0.826)/0.0315
        zero = 169.f * (tensao_alimentacao/resolucao_ad)
        vout = leitura_ad_umidade * (tensao_alimentacao/resolucao_ad)
        valor_umidade = (vout - zero) / 0.0315
        */

            //float leitura_ad_umidade = analogRead(terminal);

            float valor_umidade = ((_sinal_ad - off_set) * fator);

            return valor_umidade;
        }
    };
}
