#include "Engine.h"
//printf
#include <stdio.h>

#include "Timer.h"

KatoEngine::KatoEngine
(const char* title, unsigned int scrwidth, unsigned int scrheight) 
	: pm_scrwidth(scrwidth), pm_scrheight(scrheight), pm_title(title),
	  pm_psdlwin(0), pm_psurf(0), pm_isquit(false), pm_ptimer(new Timer())
{
	Initialize();
}

void KatoEngine::Update()
{
  SDL_Event eventhnd; //an event handler

#if defined(TIMER_TEST)
  {
    printf("Following Timer::Show should be 0.\n");
    pm_timer.Show();
    pm_timer.Start();

    printf("Following Timer::Show should be {elapsed_tick + (current_tick - init_tick)}.\n");
    pm_timer.Show();

    printf("Timer::Pause should be called once.\n");
    pm_timer.Pause();
    pm_timer.Pause();
    pm_timer.Pause();

    printf("Following Timer::Show should be (elapsed_tick).\n");
    pm_timer.Show();
    pm_timer.Stop();
    pm_timer.Start();
    pm_timer.Pause();

    printf("Timer::Unpause should be called once.\n");
    pm_timer.Unpause();
    pm_timer.Unpause();
    pm_timer.Unpause();

    printf("Following Timer::Show should be {elapsed_tick + (current_tick - init_tick)}.\n");
    pm_timer.Show();
  }
#endif

  //unsigned int countedFrames = 0;

  //start_tick & end_tick
  Uint32 stat = 0, endt;
  float dt;

  pm_ptimer->Start();

  while (!pm_isquit)
  {
    //Average FPS = number_of_frames / (time_passed / 1000.f)
    //float avgfps = countedFrames / (pm_timer.Show() / 1000.f);

    //printf("AVERAGE FPS = %f\n", avgfps);
    //printf("TIME / 1000.f = %f\n", (pm_timer.Show() / 1000.f));

    //Till the event gets emptied out.
    while (SDL_PollEvent(&eventhnd))
    {
      /*
        https://wiki.libsdl.org/SDL_EventType#Remarks
        #1 An SDL_QUIT event is generated when the user clicks
        on the close button of the last existing window.
      */
      if (eventhnd.type == SDL_QUIT)
      {
        pm_isquit = true;
        //Stop assessing for the leftover msgs, and just break.
        //break;
      }
      else if (eventhnd.type == SDL_KEYDOWN)
      {
        switch (eventhnd.key.keysym.sym)
        {
          case SDLK_UP:
          {
#if defined(_DEBUG)
            printf("UP\n");
#endif
            break;
          }
          case SDLK_DOWN:
          {
#if defined(_DEBUG)
            printf("DOWN\n");
#endif
            break;
          }
          case SDLK_LEFT:
          {
#if defined(_DEBUG)
            printf("LEFT\n");
#endif
            break;
          }
          case SDLK_RIGHT:
          {
#if defined(_DEBUG)
            printf("RIGHT\n");
#endif
            break;
          }
        }
      }
    }

    /*
      while(1)
      {
        end = SDL_GetTicks();
        dt = end - start;
        start = end;
        Function(dt);
      }
    */

    for (int i = 0; i < 100000000; ++i)
    {
      long int x = i * i * i;
      x = x  * x;
    }

    //What if timer's Uint32 value gets overflowed?
    endt = pm_ptimer->Show();
    //printf("endt - stat = %i\n", endt - stat);

    dt = (endt - stat) / 1000.f;
    stat = endt;

#if defined(_DEBUG)
    printf("dt = %f\n", dt);
#endif

    //printf("%i\n", pm_timer.Show());

    //Pretty much this is where the Render & PhysicsUpdate will be called.
    //++countedFrames;

    //PhysicsUpdate(1.f);
  }

  this->Quit();
}

void KatoEngine::Initialize()
{
  if (SDL_Init(//SDL's video subsystem
      SDL_INIT_VIDEO) < 0)
    printf("Failed to initialize SDL; %s\n", SDL_GetError());
  else
  {
    pm_psdlwin = SDL_CreateWindow(pm_title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  pm_scrwidth,
                                  pm_scrheight,
                                  SDL_WINDOW_SHOWN);
    if (!pm_psdlwin)
      printf("Failed to create Window; %s\n", SDL_GetError());
    else
    {
      //Get HDC for the window(?)
      pm_psurf = SDL_GetWindowSurface(pm_psdlwin);
      //perhaps format in the SDL_Surface struct has something to do with
      //pixelformatdescriptor(?)
      SDL_FillRect(pm_psurf, 0, SDL_MapRGB(pm_psurf->format, 0xFF, 0xFF, 0xFF));
      //SwapBuffer(?)
      SDL_UpdateWindowSurface(pm_psdlwin);
      //SDL_Delay(5000);
    }
  }
}

void KatoEngine::Quit()
{
  SDL_DestroyWindow(pm_psdlwin);
  SDL_Quit();
}