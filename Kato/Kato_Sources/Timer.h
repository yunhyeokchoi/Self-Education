#ifndef TIMER_H
#define TIMER_H

#include "Engine.h"
#include <SDL.h>

class Timer
{
  public:
    /*
      Start and timer starts counting from 0.
      Pressing Start at any situation should do one thing; Start.
    */
    void Start();
    
    /*
      Stops and it resets the number to 0.
      Do one thing no matter what; Stop.
    */
    void Stop();

    /*
      Pause the timer and the number stops being incremented.
      Do nothing when Timer is not started.
      Stop counting up the Timer when it has been started in the past.
    */
    void Pause();

    /*
      Show the Timer.
      Show 0 when Timer is not started.
      Show GetTick() - initialtick when it's not paused.
      Show elapsedtick when it's paused.
    */
    Uint32 Show();

    /*
      Unpause the timer and number starts being incremented again.
      Do nothing when Timer is not started.
      Start counting the Timer again.
    */
    void Unpause();

  private:
    //It's created only once in KatoEngine class's constructor.
    friend KatoEngine::KatoEngine(const char* title, unsigned int scrwidth, unsigned int scrheight);
    
    //No one can create this, but only in KatoEngine's ctor.
    Timer() : pm_ispause(false), pm_isstarted(false) {}

    bool pm_ispause;
    bool pm_isstarted;

    //Initial tick.
    Uint32 pm_itick;
    //Ticks elapsed 
    Uint32 pm_etick;
};

#endif
