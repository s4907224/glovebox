#include "helpers/sdl_utils.h"
#include "user_io/key_handler.h"

int gbox::sdl_scancode_to_gbox(int _scancode)
{
  if(_scancode != 0)
  {
    return _scancode - 3;
  }
  return _scancode;
}