#ifndef GBOX_CORE_H
#define GBOX_CORE_H

#define DEBUG_PRINTS

#include <iostream>
#include <memory>
#include <chrono>
#include <map>
#include <functional>

#include "helpers/gl_utils.h"

#include "handlers/generic_handler.h"
#include "handlers/sdl_handler.h"
#include "user_io/key_handler.h"
#include "user_io/key_binds.h"
#include "geometry/VAO.h"
#include "shader/shader_program.h"
#include "camera/camera.h"

namespace gbox
{
  class Core
  {
    public:
      // dtor
      ~Core();
      // ctor
      Core();
      // copy ctor
      Core(const Core& _core_other);
      // copy assignment operator
      Core& operator=(const Core& _core_other);
      // move ctor
      Core(Core&& _core_other);
      // move assignment operator
      Core& operator=(Core&& _core_other);
      // property for ID
      const int& ID() {return m_ID;}

      void register_SDL_handler();
      void register_SDL_handler(std::shared_ptr<gbox::SDLHandler> _sdl_handler);

      bool quit_requested() const;

      void register_keybind(int _scancode, int _keybind);

      void update();

      std::shared_ptr<gbox::VAO> add_VAO(std::string _model_file);

      std::shared_ptr<gbox::Shader> register_shader(std::string _shader_file);
      std::shared_ptr<gbox::ShaderProgram> register_shader_program(std::vector<std::string> _shader_files);
      std::shared_ptr<gbox::ShaderProgram> register_shader_program(std::vector<std::shared_ptr<gbox::Shader>> _shaders);

      void register_camera(std::shared_ptr<gbox::Camera> _camera);

      // void use_shader_program(std::string _shader_program_name);

    private:
      static int m_instance_counter;
      int m_ID;

      std::shared_ptr<gbox::GenericHandler> m_handler;
      std::shared_ptr<gbox::KeyHandler> m_key_handler;
      void process_keys();

      void init_triangle_VAO();
      void draw();
      void set_polygon_mode(GLenum face, GLenum mode);
      bool m_wireframe = false;

      void init_GL();

      std::vector<std::shared_ptr<gbox::VAO>> m_VAOs;

      std::vector<std::shared_ptr<gbox::Camera>> m_cameras;
      void update_cameras();

      std::map<std::string, std::shared_ptr<gbox::Shader>> m_shaders;
      std::map<std::size_t, std::shared_ptr<gbox::ShaderProgram>> m_shader_programs;

      bool m_quit;

      std::chrono::time_point<std::chrono::system_clock> m_time_of_last_update;
      float m_delta_time;
      // gbox::VAO m_vao;

  };// class Core
}// namespace gbox

#endif // GBOXCOREH