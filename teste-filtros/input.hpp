
namespace entrada
{
    const uint8_t VCC = A0;
    const uint8_t GND = A5;
    const uint8_t SAIDA = A2;

    void setup()
    {
        
        pinMode(VCC, OUTPUT);
        digitalWrite(VCC, HIGH);

        pinMode(GND, OUTPUT);
        digitalWrite(GND, LOW);
        
        pinMode(SAIDA, INPUT);
        
    }

    inline float read()
    {
        return analogRead(SAIDA);
    }
}