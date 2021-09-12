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

  core.register_keybind(gbox::GBSC_1, gbox::GBIND_wireframe_toggle);

  core.register_keybind(gbox::GBSC_W, gbox::GBIND_forward);
  core.register_keybind(gbox::GBSC_A, gbox::GBIND_left);
  core.register_keybind(gbox::GBSC_S, gbox::GBIND_backward);
  core.register_keybind(gbox::GBSC_D, gbox::GBIND_right);

  core.register_shader_program("basic", {"resources/shaders/basic/flat_colour.frag", "resources/shaders/basic/default.vert"});
  core.use_shader_program("basic");
  auto h = core.add_VAO("resources/models/ship.obj");
  glm::mat4 m1(1.f);
  m1 = glm::translate(m1, glm::vec3(0.5f, 0.0f, 0.0f));

  glm::mat4 m2(1.f);
  m2 = glm::translate(m2, glm::vec3(0.f, -0.1f, 1.f));
  GLuint m1_id;
  GLuint m2_id;
  h->register_mvp(&m1_id, std::make_shared<glm::mat4>(m1));
  h->register_mvp(&m2_id, std::make_shared<glm::mat4>(m2));

  while(!core.quit_requested())
  {
    core.update();
  }

return EXIT_SUCCESS;
}
