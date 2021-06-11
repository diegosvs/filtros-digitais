class Temperatura
{
private:
    
    const int terminal;
    const float fator;
    const float resistor_serie;
    float resistencia_termistor;
    //float temperatura;

public:
    float temperatura;
    
    Temperatura(const int &_terminal, 
                const float &_tensao_alimentacao, 
                const float &_resistor_serie):
                
                terminal (_terminal), 
                fator (_tensao_alimentacao / 1023.f),
                resistor_serie (_resistor_serie) {}

    
int lerTemperatura()
{
    //resistencia_termistor = (tensao_alimentacao * resistor_serie * analogRead(terminal)) - resistor_serie;
    
    //resistencia_termistor = ((1023.f * fator) / (fator * analogRead(terminal))) * resistor_serie - resistor_serie ;
    
    temperatura = log(resistencia_termistor);
    temperatura = 1.f / (0.001129148f + (0.000234125f * temperatura) 
    + (0.0000000876741f * temperatura * temperatura * temperatura)
    );

    //temperatura = 3600.f / log (resistencia_termistor/(10000.f * exp(-3600.f / (273.f+25.f) ) ) );
    
    
    //temperatura = temperatura - 273.15f;

    //return temperatura;
      
    return analogRead(terminal);
}    
};
