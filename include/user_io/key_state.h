#ifndef GBOX_KEYSTATE_H
#define GBOX_KEYSTATE_H

#include <iostream>

namespace gbox
{
  struct KeyState
  {
    public:
      // dtor
      KeyState();
      KeyState(int _keycode);
      ~KeyState() = default;
      // ctor
      bool pressed;
      bool just_pressed;
      bool just_released;
      int keycode;

  };// struct KeyState
}// namespace gbox

#endif // GBOXKEYSTATEH