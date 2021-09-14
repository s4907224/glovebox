#include <iostream>
#include <cmath>
#include <functional>

#include "core/core.h"
#include "user_io/key_handler.h"
#include "user_io/key_binds.h"
#include "geometry/mesh.h"


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

  auto shader_program = core.register_shader_program({"resources/shaders/basic/basic.frag", "resources/shaders/basic/default.vert"});
  auto shader_program2 = core.register_shader_program({"resources/shaders/basic/basic.frag", "resources/shaders/basic/default.vert"});
  auto shader_program3 = core.register_shader_program({"resources/shaders/basic/flat_colour.frag", "resources/shaders/basic/default.vert"});
  shader_program->use();
  
  auto h = core.add_VAO("resources/models/bust.obj");

  glm::mat4 view = glm::lookAt(glm::vec3(.5f, 1.f, 5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
  glm::mat4 proj = glm::perspective(glm::radians(90.f), 4.0f / 3.0f, 0.1f, 100.0f);

  std::shared_ptr<gbox::Mesh> mesh = std::make_shared<gbox::Mesh>();
  mesh->set_model_matrix(glm::mat4(1.f));
  mesh->set_view_matrix(view);
  mesh->set_projection_matrix(proj);
  mesh->set_shader_program(shader_program);

  std::shared_ptr<gbox::Mesh> mesh2 = std::make_shared<gbox::Mesh>();
  mesh2->set_model_matrix(glm::mat4(1.f));
  mesh2->set_view_matrix(view);
  mesh2->set_projection_matrix(proj);
  mesh2->set_shader_program(shader_program3);


  h->register_mesh(mesh);
  h->register_mesh(mesh2);

  int flip = 0;
  int frames = 0;

  while(!core.quit_requested())
  {
    core.update();
    mesh->translate(glm::vec3(0.01f, 0.f, 0.f));
    mesh2->set_model_matrix(glm::translate(glm::mat4(1.f), glm::vec3(-4.f, sin(float(frames++) * 0.5f) * 0.1f, 0.f)));
  }

return EXIT_SUCCESS;
}
