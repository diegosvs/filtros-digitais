namespace config
{
    int terminal_ad = A0;

    int terminal_umidade = 10;    //D1 - GPIO5
    int terminal_temperatura = 9; //D0 - GPIO16

    void setup()
    {
        pinMode(terminal_ad, INPUT);
        pinMode(terminal_umidade, OUTPUT);
        pinMode(terminal_temperatura, OUTPUT);
        digitalWrite(terminal_temperatura, HIGH);
        digitalWrite(terminal_umidade, HIGH);
    }

    inline float sinalAD()
    {
        return analogRead(terminal_ad);
    }

    void ativaTemperatura()
    {
        digitalWrite(terminal_temperatura, LOW);
        digitalWrite(terminal_umidade, HIGH);
    }

    void ativaUmidade()
    {
        digitalWrite(terminal_umidade, LOW);
        digitalWrite(terminal_temperatura, HIGH);
    }
} // namespace config
