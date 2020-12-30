#include <iostream>

#include "core/core.h"
#include "user_io/key_handler.h"
#include "user_io/key_binds.h"

int main()
{
  gbox::Core core;
  core.register_SDL_handler();

  core.register_keybind(gbox::GBSC_F, gbox::GBIND_fullscreen_toggle);
  core.register_keybind(gbox::GBSC_escape, gbox::GBIND_exit);
  core.register_shader_program("basic", {"shaders/basic/flat_colour.frag", "shaders/basic/default.vert"});
  core.use_shader_program("basic");
  auto h = core.add_VAO("test");

  while(!core.quit_requested())
  {
    core.update();
  }

return EXIT_SUCCESS;
}
