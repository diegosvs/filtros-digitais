namespace TH
{

    class Temperatura
    {
    private:
        const float resistor_serie;
        const float resolucao_ad;
        const float off_set;
        float resistencia_termistor;
        float temperatura;

    public:
        Temperatura(const float &_resolucao_ad,
                    const float &_resistor_serie,
                    const float &_offset) :

                                                    resolucao_ad(pow(2, _resolucao_ad)),
                                                    resistor_serie(_resistor_serie),
                                                    off_set(_offset)
        {
        }

        float lerTemperatura(const float &_sinal_ad)
        {

            resistencia_termistor = ((resolucao_ad / _sinal_ad) * resistor_serie) - resistor_serie;

            temperatura = log(resistencia_termistor);
            temperatura = 1.f / (0.001129148f + (0.000234125f * temperatura) + (0.0000000876741f * temperatura * temperatura * temperatura));

            //temperatura = 3600.f / log (resistencia_termistor/(10000.f * exp(-3600.f / (273.f+25.f) ) ) );

            temperatura = temperatura - 273.5f + off_set;

            return temperatura;
        }
    };
}
