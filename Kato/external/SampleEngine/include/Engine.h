#ifndef ENGINE_H
#define ENGINE_H

//std::list<SDL_Surface*>, std::list<System*>
#include <SDL.h>

#include <list>

//Putting these into KatoEngine namespace would cause an incompatibility issue,
//in a situation where a pointer returned by one of SDL functions should be assigned.
//struct SDL_Surface;
//struct SDL_Window;

namespace KatoEngine
{
  class Timer;
  class System;

  class Engine
  {
    public:
      Engine(const char* title, unsigned int scrwidth, unsigned int scrheight);
      ~Engine();
      void Update();

    private:
      void Initialize();
      void PhysicsUpdate(float/* dt*/) {}
      void Quit();
      
      bool PollWindowEvent(SDL_Event& currEvent);
      void PollKeyboardEvent(SDL_Event& currEvent);

      unsigned int pm_scrwidth;
      unsigned int pm_scrheight;
      const char* pm_title;

      SDL_Window* pm_psdlwin;
      SDL_Surface* pm_psurf;

      bool pm_isquit;
      std::list<System*> pm_listpsys;
      std::list<SDL_Surface*> pm_listpimage;
      Timer* pm_ptimer;
  };
}

#endif