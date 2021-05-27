
namespace entrada
{
    const uint8_t VCC = A0;
    const uint8_t GND = A5;
    const uint8_t TEMPERATURA = A2;
    const uint8_t UMIDADE = A4; 

    


    void setup()
    {
        

        pinMode(VCC, OUTPUT);
        digitalWrite(VCC, HIGH);

        pinMode(GND, OUTPUT);
        digitalWrite(GND, LOW);
        
        pinMode(TEMPERATURA, INPUT);
        pinMode(UMIDADE, INPUT);
        
    }

    inline float readTemperatura()
    {
        return analogRead(TEMPERATURA);
        //return digitalRead(TEMPERATURA);
        
    }

    inline float readUmidade()
    {
        //return digitalRead(UMIDADE);
        return analogRead(UMIDADE);
    }
}
