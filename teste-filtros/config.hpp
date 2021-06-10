
namespace config
{
    //const uint8_t VCC = A0;
    //const uint8_t GND = A5;
    const uint8_t TEMPERATURA = A0;
    const uint8_t UMIDADE = A5; 

    void terminais()
    {
        /*
        pinMode(VCC, OUTPUT);
        digitalWrite(VCC, HIGH);
        pinMode(GND, OUTPUT);
        digitalWrite(GND, LOW);
        */
               
        pinMode(TEMPERATURA, INPUT);
        pinMode(UMIDADE, INPUT);
        
    }

    inline float lerTemperatura()
    {
        float leitura_ad_temperatura = analogRead(TEMPERATURA);
        float valor_temperatura;
        
        /*
                    // Conexão do termistor
            const int pinTermistor = A0;
            
            // Parâmetros do termistor
            const double beta = 3600.0;
            const double r0 = 10000.0;
            const double t0 = 273.0 + 25.0;
            const double rx = r0 * exp(-beta/t0);
            
            // Parâmetros do circuito
            const double vcc = 5.0;
            const double R = 20000.0;
            
            // Numero de amostras na leitura
            const int nAmostras = 5;
            
            // Iniciação
            void setup() {
            Serial.begin(9600);
            }
            
            // Laço perpétuo
            void loop() {
            // Le o sensor algumas vezes
            int soma = 0;
            for (int i = 0; i < nAmostras; i++) {
                soma += analogRead(pinTermistor);
                delay (10);
            }
            
            // Determina a resistência do termistor
            double v = (vcc*soma)/(nAmostras*1024.0);
            double rt = (vcc*R)/v - R;
            
            // Calcula a temperatura
            double t = beta / log(rt/rx);
            Serial.println (t-273.0);
            
            // Dá um tempo entre leituras
            delay (10000);
            }
                    */


        return valor_temperatura;
    }

    inline float lerUmidade()
    {
            /*
        5V / 1023bits= 0,0048V/bit
        0%    ur --> 0,826V --> 172 bits
        75,3% ur --> 3,198V --> 666 bits 
        666 - 172 = 494 divisões
        494 / 75,3 = 6,56 --> 0,1% ur
        */

        float leitura_ad_umidade = analogRead(UMIDADE);
        float valor_umidade = (leitura_ad_umidade - 172.f) / 6.56f;
       

        if (leitura_ad_umidade < 172.f)
        {
            return valor_umidade = 0.f;
        }

        else if (leitura_ad_umidade >= 828.f)
        {
            return valor_umidade = 100.f;
        }       

        else
        {      
            return valor_umidade;
        }
    }
}
