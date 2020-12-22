#include "user_io/key_state.h"

gbox::KeyState::KeyState() : 
  pressed(false),
  just_pressed(false),
  just_released(false),
  keycode(0)
{}

gbox::KeyState::KeyState(int _keycode) : 
  pressed(false),
  just_pressed(false),
  just_released(false),
  keycode(_keycode)
{}