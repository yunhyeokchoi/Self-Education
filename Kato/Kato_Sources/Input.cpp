#include "Input.h"

#include <bitset>
namespace KatoEngine
{
  //Keep track of things that are pressed, triggered, or released.
  std::bitset<SDL_NUM_SCANCODES> s_pressed;
  std::bitset<SDL_NUM_SCANCODES> s_triggered;
  std::bitset<SDL_NUM_SCANCODES> s_released;

  void Input::Initialize()
  {
    for (unsigned int i = 0; i < SDL_NUM_SCANCODES; ++i)
    {
      s_pressed[i] = s_triggered[i] = s_released[i] = false;
    }
  }

  void Input::SetKeyPressed(SDL_Scancode key, SDL_EventType keystatus)
  {
    if (key < SDL_SCANCODE_UNKNOWN ||
        key > SDL_NUM_SCANCODES)
    {
      //Invalid input.
    }

    //If the key is pressed.
    if (keystatus == SDL_KEYDOWN)
    {
      s_pressed[key] = true;
      s_triggered[key] = true;
    }
    else if (keystatus == SDL_KEYUP)
    {
      s_released[key] = true;
      s_pressed[key] = false;
    }
  }

  bool Input::IsPressed(SDL_Scancode key)
  {
    return s_pressed[key];
  }

  bool Input::IsReleased(SDL_Scancode key)
  {
    return s_released[key];
  }

  bool Input::IsTriggered(SDL_Scancode key)
  {
    return s_triggered[key];
  }

  bool Input::IsAnyPressed()
  {
    return s_pressed.any();
  }

  bool Input::IsAnyTriggered()
  {
    return s_triggered.any();
  }

  bool Input::IsAnyReleased()
  {
    return s_released.any();
  }
}