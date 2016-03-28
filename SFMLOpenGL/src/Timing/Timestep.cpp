
#include <Timing\Timestep.h>

#include <math.h>

Timestep::Timestep()
{
    //ctor
    accumulator = 0;
	mRenderclock.restart();
}

Timestep::~Timestep()
{
    //dtor
}

void Timestep::startLoop()
{
     /*
     Update sinceLastUpdate
     Add this duration to the accumulator.
     */

     sinceLastUpdate = mClock.restart().asSeconds();
     if (sinceLastUpdate > TIMESTEP * 5)
        sinceLastUpdate = TIMESTEP * 5;
    accumulator += sinceLastUpdate;
    while (accumulator > (TIMESTEP * frameSkip))
    {
        accumulator -= TIMESTEP;
    }

}

bool Timestep::canUpdate()
{
    /*
    Only allow game to update if:
        - More than TIMESTEP has elapsed since the last loop

        Once more time has been spent updating than a single timestep,
        stop updating
    */


    bool allowUpdate = (accumulator > TIMESTEP);
    if (allowUpdate)
    accumulator -= TIMESTEP;
    return allowUpdate;

}


float Timestep::getAlpha()
{
	return mRenderclock.restart().asSeconds();
}