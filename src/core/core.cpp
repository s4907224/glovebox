#include "core/core.h"

int gbox::Core::m_instance_counter = 0;

gbox::Core::Core() :
  m_quit(false),
  m_time_of_last_update(std::chrono::system_clock::now())
{
  m_ID = m_instance_counter++;

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for Core with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Core::~Core()
{
  #ifdef DEBUG_PRINTS
  std::cout<<"Dtor called for Core with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Core::Core(const Core& _core_other)
{
  m_ID = m_instance_counter++;
  m_handler = _core_other.m_handler;
  m_key_handler = _core_other.m_key_handler;
  m_VAOs = _core_other.m_VAOs;
  m_quit = _core_other.m_quit;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<std::dec<<'\n';
  #endif
}

gbox::Core& gbox::Core::operator=(const Core& _core_other)
{
  m_ID = _core_other.m_ID;
  m_handler = _core_other.m_handler;
  m_key_handler = _core_other.m_key_handler;
  m_VAOs = _core_other.m_VAOs;
  m_quit = _core_other.m_quit;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<std::dec<<'\n';
  #endif

  return *this;
}

gbox::Core::Core(Core&& _core_other)
{
  m_ID = _core_other.m_ID;
  m_handler = _core_other.m_handler;
  m_key_handler = _core_other.m_key_handler;
  m_VAOs = _core_other.m_VAOs;
  m_quit = _core_other.m_quit;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<std::dec<<'\n';
  #endif

  _core_other.m_ID = -1;
}

gbox::Core& gbox::Core::operator=(Core&& _core_other)
{
  m_ID = _core_other.m_ID;
  m_handler = _core_other.m_handler;
  m_key_handler = _core_other.m_key_handler;
  m_VAOs = _core_other.m_VAOs;
  m_quit = _core_other.m_quit;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<std::dec<<'\n';
  #endif

  _core_other.m_ID = -1;
  return *this;
}

void gbox::Core::register_SDL_handler()
{
  m_handler = std::make_shared<gbox::SDLHandler>();

  init_GL();
}

void gbox::Core::update()
{
  auto now = std::chrono::system_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_time_of_last_update);
  m_time_of_last_update = std::chrono::system_clock::now();

  int delta_time = duration.count();

  m_handler->update();

  process_keys();

  update_cameras();

  draw();
}

void gbox::Core::process_keys()
{
  for(std::shared_ptr<gbox::KeyState> keystate: m_handler->get_key_handler().get_active_keys())
  {
    for(int keybind : m_handler->get_key_handler().get_keybinds(keystate->scancode))
    {
      switch(keybind)
      {
        case (GBIND_fullscreen_toggle):
        {
          if (not keystate->just_pressed)
          {
            break;
          }
          m_handler->toggle_fullscreen();
          break;
        }
        case (GBIND_exit):
        {
          m_handler->request_quit();
          m_quit = true;
          break;
        }

        case (GBIND_wireframe_toggle):
        {
          if (not keystate->just_pressed)
          {
            break;
          }

          m_wireframe = not m_wireframe;

          if (m_wireframe)
          {
            set_polygon_mode(GL_FRONT_AND_BACK, GL_LINE);
          }
          else
          {
            set_polygon_mode(GL_FRONT_AND_BACK, GL_FILL);
          }
          break;
        }

        case (GBIND_forward):
        {
          for (auto camera : m_cameras)
          {
            camera->view_space_translate({0.f, 0.f, 0.1f});
          }
          break;
        }

        case (GBIND_backward):
        {
          for (auto camera : m_cameras)
          {
            camera->view_space_translate({0.f, 0.f, -0.1f});
          }
          break;
        }

        case (GBIND_left):
        {
          for (auto camera : m_cameras)
          {
            camera->view_space_translate({-0.1f, 0.f, 0.f});
          }
          break;
        }

        case (GBIND_right):
        {
          for (auto camera : m_cameras)
          {
            camera->view_space_translate({0.1f, 0.f, 0.f});
          }
          break;
        }
      }
    }
  }
}

void gbox::Core::init_GL()
{
  if(glewInit() != GLEW_OK)
  {
    std::cout << "Glew Failed to Initialise\n";
  }

  std::cout << "Version: " << glGetString(GL_VERSION) << " :Version " << std::endl;
}

void gbox::Core::draw()
{
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  for (auto &m_vao : m_VAOs)
  {
    m_vao->draw();
  }
}

void gbox::Core::set_polygon_mode(GLenum face, GLenum mode)
{
  glPolygonMode(face, mode);
}

bool gbox::Core::quit_requested() const
{
  return m_quit;
}

void gbox::Core::register_keybind(int _scancode, int _keybind)
{
  m_handler->register_keybind(_scancode, _keybind);
}

std::shared_ptr<gbox::VAO> gbox::Core::add_VAO(std::string _model_file)
{
  m_VAOs.push_back(std::make_shared<gbox::VAO>(_model_file));
  return m_VAOs.back();
}

std::shared_ptr<gbox::Shader> gbox::Core::register_shader(std::string _shader_file)
{
  if (m_shaders.find(_shader_file) == m_shaders.end())
  {
    std::shared_ptr<gbox::Shader> shader = std::make_shared<gbox::Shader>(_shader_file);
    shader->compile();
    m_shaders.insert(std::make_pair(_shader_file, shader));
  }
  
  return m_shaders[_shader_file]; 
}

std::shared_ptr<gbox::ShaderProgram> gbox::Core::register_shader_program(std::vector<std::string> _shader_files)
{
  std::size_t combined_hash = 0;

  for (auto shader_file : _shader_files)
  {
    combined_hash = std::hash<std::size_t>{}(combined_hash + std::hash<std::string>{}(shader_file));
  }

  if (m_shader_programs.find(combined_hash) == m_shader_programs.end())
  {
    std::vector<std::shared_ptr<gbox::Shader>> shaders;

    for (auto shader_file : _shader_files)
    {
      shaders.push_back(register_shader(shader_file));
    }

    std::shared_ptr<gbox::ShaderProgram> shader_program =  std::make_shared<gbox::ShaderProgram>(shaders);
    m_shader_programs.insert(std::make_pair(combined_hash, shader_program));
  }
  
  return m_shader_programs[combined_hash];
}

void gbox::Core::register_camera(std::shared_ptr<gbox::Camera> _camera)
{
  m_cameras.push_back(_camera);
}

void gbox::Core::update_cameras()
{
  for (auto camera : m_cameras)
  {
    camera->update_view_projection_matrix();
  }
}