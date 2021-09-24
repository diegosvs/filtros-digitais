namespace config
{
    const int sinal_t = 32; //adc1_ch4 gpio 32
    const int sinal_h = 33; //adc1_ch5 gpio 33

    void setup()
    {
        pinMode(2, OUTPUT);
        pinMode(sinal_t, INPUT);
        pinMode(sinal_h, INPUT);
    }

    inline float sinalADTemperatura()
    {
        return analogRead(sinal_t);
    }

    inline float sinalADUmidade()
    {
        return analogRead(sinal_h);
    }

} // namespace config
