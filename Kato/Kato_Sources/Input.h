#ifndef INPUT_H
#define INPUT_H
#include <SDL.h>

namespace KatoEngine
{
  class Input
  {
    public:
      void Initialize();

      //Sets pressed, triggered, released, or unpressed status of a key.
      void SetKeyPressed(SDL_Scancode key, SDL_EventType keystatus);

      //Input();
      //~input();

      //Check if a specific key is pressed, triggered, released.
      bool IsPressed(SDL_Scancode key);
      bool IsReleased(SDL_Scancode key);
      bool IsTriggered(SDL_Scancode key);

      //Check if any keys are pressed, triggered, or released.
      bool IsAnyPressed();
      bool IsAnyTriggered();
      bool IsAnyReleased();

    private:
  };
}

#endif