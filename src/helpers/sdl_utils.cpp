#include "helpers/sdl_utils.h"
#include "user_io/key_handler.h"

int gbox::sdl_keycode_to_gbox(int _keycode)
{
  if (_keycode >= 32)
  {
    if (_keycode <= 64)
    {
      return _keycode - 26;
    }

    if (_keycode <= 122)
    {
      return _keycode - 52;
    }

    if (_keycode == 127)
    {
      return 71;
    }

    return _keycode - 1073741809;
  }

  if (_keycode != 0)
  {
    return _keycode - 2;
  }
  return 0;
}