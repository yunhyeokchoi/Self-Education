#include "Timer.h"

namespace KatoEngine
{
  void Timer::Start()
  {
    //Initialize the Timer to clean slate.
    Stop();

    pm_isstarted = true;

    //Setting up the initial tick, so that we can take out
    //what it's storing after the Timer's been paused.
    pm_itick = SDL_GetTicks();

//#if defined(TIMER_TEST)
//    printf("Timer::Start();\n");
//#endif
  }

  void Timer::Stop()
  {
    pm_isstarted = false;
    pm_ispause = false;
    pm_itick = 0;
    pm_etick = 0;

//#if defined(TIMER_TEST)
//    printf("Timer::Stop();\n");
//#endif
  }

  void Timer::Pause()
  {
    if (pm_isstarted &&
      //It disables client prompting Pause multiple times,
      //when Timer is paused.
      !pm_ispause)
    {
      pm_ispause = true;
      //pm_etick is accumulated as the number of calls to Pause increases.
      pm_etick += SDL_GetTicks() - pm_itick;

//#if defined(TIMER_TEST)
//      printf("Timer::Pause();\n");
//#endif
    }
  }

  Uint32 Timer::Show()
  {
    if (pm_isstarted)
    {
      if (pm_ispause)
      {
//#if defined(TIMER_TEST)
//        printf("Timer::Show() : (elapsed_tick)\n");
//#endif
        return pm_etick;
      }
      else
      {
//#if defined(TIMER_TEST)
//        printf("Timer::Show() : {elapsed_tick + (current_tick - init_tick)}\n");
//#endif
        return pm_etick + SDL_GetTicks() - pm_itick;
      }
    }

//#if defined(TIMER_TEST)
//    printf("Timer::Show() : 0\n");
//#endif
    return 0;
  }

  void Timer::Unpause()
  {
    if (pm_isstarted &&
      //It disables client prompting Unpause multiple times,
      //when Timer is paused.
      pm_ispause)
    {
      pm_ispause = false;
      pm_itick = SDL_GetTicks();

//#if defined(TIMER_TEST)
//      printf("Timer::Unpause();\n");
//#endif
    }
  }

  /*void Timer::TimerTest()
  {
    printf("Following Timer::Show should be 0.\n");
    Show();
    Start();

    printf("Following Timer::Show should be {elapsed_tick + (current_tick - init_tick)}.\n");
    Show();

    printf("Timer::Pause should be called once.\n");
    Pause();
    Pause();
    Pause();

    printf("Following Timer::Show should be (elapsed_tick).\n");
    Show();
    Stop();
    Start();
    Pause();

    printf("Timer::Unpause should be called once.\n");
    Unpause();
    Unpause();
    Unpause();

    printf("Following Timer::Show should be {elapsed_tick + (current_tick - init_tick)}.\n");
    Show();
  }*/
}