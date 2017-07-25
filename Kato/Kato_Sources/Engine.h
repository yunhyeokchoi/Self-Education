#ifndef ENGINE_H
#define ENGINE_H

//#include "Timer.h"
//std::list<SDL_Surface*>
#include <list>
//SDL_Init(), ...
#include <SDL.h>

class Timer;

//class SDL_Window;
//class SDL_Surface;

class KatoEngine
{
  public:
	  KatoEngine(const char* title, unsigned int scrwidth, unsigned int scrheight);
    ~KatoEngine();
    void Update();

  private:
    void Initialize();
	  void PhysicsUpdate(float/* dt*/){}
    void Quit();

	  unsigned int pm_scrwidth;
	  unsigned int pm_scrheight;
	  const char* pm_title;

	  SDL_Window* pm_psdlwin;
	  SDL_Surface* pm_psurf;

	  bool pm_isquit;
	  std::list<SDL_Surface*> pm_listpimage;
	  Timer* pm_ptimer;
};

#endif