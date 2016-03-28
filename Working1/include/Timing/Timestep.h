#ifndef TIMESTEP_H
#define TIMESTEP_H

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Timestep
{
    public:
        const float TIMESTEP = 1/60.f;
        Timestep();
        virtual ~Timestep();
        void startLoop();
        bool canUpdate();
        float getAlpha();
    protected:
    private:
        sf::Clock mClock, mRenderclock;
        float accumulator;
        float sinceLastUpdate;
        const int frameSkip = 10;


};

#endif // TIMESTEP_H
