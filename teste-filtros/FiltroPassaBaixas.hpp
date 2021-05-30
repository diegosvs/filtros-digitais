

class FiltroPassaBaixas
{

    private:
        float k;
        float state;

    public:
        FiltroPassaBaixas(const float &k)
        {
            this->k = k;
        }

    float update(const float &input)
    {
        this-> state = this->state * this->k + (1.f - this->k )* input;

        return this->state;
        
    }

};