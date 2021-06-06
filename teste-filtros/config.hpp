
namespace config
{
    const uint8_t VCC = A0;
    const uint8_t GND = A5;
    const uint8_t TEMPERATURA = A2;
    const uint8_t UMIDADE = A4; 

    void terminais()
    {
        pinMode(VCC, OUTPUT);
        digitalWrite(VCC, HIGH);

        pinMode(GND, OUTPUT);
        digitalWrite(GND, LOW);
        
        pinMode(TEMPERATURA, INPUT);
        pinMode(UMIDADE, INPUT);
        
    }

    inline float lerTemperatura()
    {
        return analogRead(TEMPERATURA);
        //return digitalRead(TEMPERATURA);
        
    }

    inline float lerUmidade()
    {
        //return digitalRead(UMIDADE);
        return analogRead(UMIDADE);
    }
}
