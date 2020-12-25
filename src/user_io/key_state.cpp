#include "user_io/key_state.h"

gbox::KeyState::KeyState() : 
  pressed(false),
  just_pressed(false),
  just_released(false),
  scancode(0)
{}

gbox::KeyState::KeyState(int _scancode) : 
  pressed(false),
  just_pressed(false),
  just_released(false),
  scancode(_scancode)
{}