#include <iostream>
#include <cmath>
#include <functional>

#include "core/core.h"
#include "user_io/key_handler.h"
#include "user_io/key_binds.h"
#include "geometry/mesh.h"
#include "camera/perspective_camera.h"


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

  std::shared_ptr<gbox::PerspectiveCamera> camera = std::make_shared<gbox::PerspectiveCamera>();
  core.register_camera(camera);

  std::shared_ptr<gbox::Mesh> mesh = std::make_shared<gbox::Mesh>();
  mesh->set_camera(camera);
  mesh->set_shader_program(shader_program);

  std::shared_ptr<gbox::Mesh> mesh2 = std::make_shared<gbox::Mesh>();
  mesh2->set_camera(camera);
  mesh2->set_shader_program(shader_program3);
  mesh2->set_model_matrix(glm::translate(glm::mat4(1.f), glm::vec3(-4.f, 0.f, 0.f)));

  h->register_mesh(mesh);
  h->register_mesh(mesh2);

  int flip = 0;
  int frames = 0;

  while(!core.quit_requested())
  {
    core.update();
  }

return EXIT_SUCCESS;
}
