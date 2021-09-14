#include <iostream>

#include <functional>

#include "core/core.h"
#include "user_io/key_handler.h"
#include "user_io/key_binds.h"
#include "geometry/mesh.h"

int main()
{

  std::size_t h1 = std::hash<std::string>{}(std::string("hello"));
  std::size_t h2 = std::hash<std::string>{}(std::string("there"));
  std::size_t h3 = std::hash<std::size_t>{}(h1 + h2);
  std::size_t h4 = std::hash<std::size_t>{}(h2 + h1);

  if(h3==h4)
  {
    std::cout<<"same!\n";
  }
  else
  {
    std::cout<<"different!\n";
  }
  

  gbox::Core core;
  core.register_SDL_handler();

  core.register_keybind(gbox::GBSC_F, gbox::GBIND_fullscreen_toggle);
  core.register_keybind(gbox::GBSC_escape, gbox::GBIND_exit);

  core.register_keybind(gbox::GBSC_1, gbox::GBIND_wireframe_toggle);

  core.register_keybind(gbox::GBSC_W, gbox::GBIND_forward);
  core.register_keybind(gbox::GBSC_A, gbox::GBIND_left);
  core.register_keybind(gbox::GBSC_S, gbox::GBIND_backward);
  core.register_keybind(gbox::GBSC_D, gbox::GBIND_right);

  auto shader_program = core.register_shader_program({"resources/shaders/basic/basic.frag", "resources/shaders/basic/default.vert"});
  auto shader_program2 = core.register_shader_program({"resources/shaders/basic/basic.frag", "resources/shaders/basic/default.vert"});
  auto shader_program3 = core.register_shader_program({"resources/shaders/basic/flat_colour.frag", "resources/shaders/basic/default.vert"});
  shader_program->use();
  
  auto h = core.add_VAO("resources/models/bust.obj");

  glm::mat4 view = glm::lookAt(glm::vec3(.5f, 1.f, 5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
  glm::mat4 proj = glm::perspective(glm::radians(90.f), 4.0f / 3.0f, 0.1f, 100.0f);

  gbox::Mesh model(h);
  model.set_model_matrix(glm::mat4(1.f));
  model.set_view_matrix(view);
  model.set_projection_matrix(proj);

  int flip = 0;
  int frames = 0;

  while(!core.quit_requested())
  {
    if (frames++ % 60 == 0)
    {
      flip++;

      if (flip==0) {shader_program->use();}
      if (flip==1) {shader_program2->use();}
      if (flip==2) {shader_program3->use();}

      flip = flip % 3;
    }
    core.update();
    model.translate(glm::vec3(0.01f, 0.f, 0.f));
  }

return EXIT_SUCCESS;
}
