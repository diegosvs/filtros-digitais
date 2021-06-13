namespace TH
{

class Temperatura
{
private:
    
    //const int terminal;
    const float fator;
    const float resistor_serie;
    const float resolucao_ad;
    float resistencia_termistor;
    float temperatura;
    

public:
    
    
    Temperatura(const float &_resolucao_ad, 
                const float &_tensao_alimentacao, 
                const float &_resistor_serie):
                
                resolucao_ad (_resolucao_ad), 
                fator (_tensao_alimentacao / resolucao_ad),
                resistor_serie (_resistor_serie) {}

    
float lerTemperatura(const float &_sinal_ad)
{
    //resistencia_termistor = (tensao_alimentacao * resistor_serie * analogRead(terminal)) - resistor_serie;
    
    resistencia_termistor = ((resolucao_ad * fator) / (fator * _sinal_ad)) * resistor_serie - resistor_serie ;
    
    
    temperatura = log(resistencia_termistor);
    temperatura = 1.f / (0.001129148f + (0.000234125f * temperatura) 
    + (0.0000000876741f * temperatura * temperatura * temperatura)
    );

    //temperatura = 3600.f / log (resistencia_termistor/(10000.f * exp(-3600.f / (273.f+25.f) ) ) );
        
    temperatura = temperatura - 273.f;

    return (temperatura,1);
      
    //return _sinal_ad;
}    
};
}

