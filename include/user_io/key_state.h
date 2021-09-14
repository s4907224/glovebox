#ifndef GBOX_KEYSTATE_H
#define GBOX_KEYSTATE_H

#define DEBUG_PRINTS

#include <iostream>

namespace gbox
{
  struct KeyState
  {
    public:
      // dtor
      KeyState();
      KeyState(int _scancode);
      ~KeyState() = default;
      // ctor
      bool pressed;
      bool just_pressed;
      bool just_released;
      int scancode;

  };// struct KeyState
}// namespace gbox

#endif // GBOXKEYSTATEH