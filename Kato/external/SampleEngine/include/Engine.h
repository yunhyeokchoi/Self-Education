#ifndef ENGINE_H
#define ENGINE_H

//std::list<SDL_Surface*>, std::list<System*>
#include <SDL.h>

#include <list>

#include <string>

//GLuint
#include <GL\glew.h>
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
      Engine(const char* title, unsigned int scrwidth, unsigned int scrheight, std::string strexepath);
      ~Engine();
      void Update();

    private:
      GLuint ReadShaderSource(GLenum shadertype, const char* filename);
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
      SDL_GLContext pm_hglContext;

      bool pm_isquit;
      std::list<System*> pm_listpsys;
      std::list<SDL_Surface*> pm_listpimage;
      Timer* pm_ptimer;
      GLuint pm_hprogram;
      const std::string pm_strexepath;
      GLuint pm_primitive;
  };
}

#endif