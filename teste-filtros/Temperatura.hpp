namespace TH
{

class Temperatura
{
private:
    
    const float resistor_serie;
    const float resolucao_ad;
    const float tensao_alimentacao;
    float resistencia_termistor;
    float temperatura;
        

public:    
    
    Temperatura(const float &_resolucao_ad, 
                const float &_tensao_alimentacao, 
                const float &_resistor_serie):
                
                resolucao_ad (_resolucao_ad), 
                tensao_alimentacao(_tensao_alimentacao),
                resistor_serie (_resistor_serie) {}
                

    
float lerTemperatura(const float &_sinal_ad)
{
       
    resistencia_termistor = ((resolucao_ad * (tensao_alimentacao/resolucao_ad)) / ((tensao_alimentacao/resolucao_ad) * _sinal_ad)) * resistor_serie - resistor_serie ;
        
    temperatura = log(resistencia_termistor);
    temperatura = 1.f / (0.001129148f + (0.000234125f * temperatura) 
    + (0.0000000876741f * temperatura * temperatura * temperatura)
    );

    //temperatura = 3600.f / log (resistencia_termistor/(10000.f * exp(-3600.f / (273.f+25.f) ) ) );
        
    temperatura = temperatura - 273.f;

    return temperatura;
   
}  

};
}

