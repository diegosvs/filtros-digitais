class Umidade
{
private:
    //const int terminal;
    const float fator;
    
       
    
public:
    Umidade(//const int &_terminal,
            const float &_tensao_alimentacao) :
            //terminal(_terminal),
            fator(_tensao_alimentacao / 1023.0f)
            {}


    float lerUmidade(const float &_sinal_ad)
    {
        /*
        5V / 1023bits= 0,0032V/bit
        0%    ur --> 0,826V --> 169 bits
        75,3% ur --> 3,198V --> 633,6 bits 
        666 - 172 = 741 divisões
        741 / 75,3 = 9,84 --> 0,1% ur
        offset - 0.826 V
        slope = 31.483 mV/%RH
        (VOUT - zero offset)/slope
        ur = (VOUT - 0.826)/0.0315
        zero = 169.f * fator
        vout = leitura_ad_umidade * fator
        valor_umidade = (vout - zero) / 0.0315
        */

        
        //float leitura_ad_umidade = analogRead(terminal);

        float valor_umidade = (_sinal_ad * fator - 169.f * fator) / 0.0315f;
        
            return valor_umidade;
            //return _sinal_ad;
        
    }
};
