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

  for(std::shared_ptr<gbox::KeyState> keystate: m_handler->get_key_handler().get_active_keys())
  {
    for(int keybind : m_handler->get_key_handler().get_keybinds(keystate->scancode))
    {
      switch(keybind)
      {
        case (GBIND_fullscreen_toggle):
        {
          if (keystate->just_pressed)
          {
            m_handler->toggle_fullscreen();
          }
          break;
        }
        case (GBIND_exit):
        {
          m_handler->request_quit();
          m_quit = true;
          break;
        }
      }
    }
  }
  draw();
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

bool gbox::Core::quit_requested() const
{
  return m_quit;
}

void gbox::Core::register_keybind(int _scancode, int _keybind)
{
  m_handler->register_keybind(_scancode, _keybind);
}

const gbox::VAO& gbox::Core::add_VAO(std::string _model_file)
{
  m_VAOs.push_back(std::make_shared<gbox::VAO>(_model_file));
  return *m_VAOs.back();
}

std::shared_ptr<gbox::Shader> gbox::Core::register_shader(std::string _shader_file)
{
  std::shared_ptr<gbox::Shader> shader = std::make_shared<gbox::Shader>(_shader_file);
  if(m_shaders.insert(std::make_pair(_shader_file, shader)).second == true)
  {
    shader->compile();
  }
  return m_shaders[_shader_file];
}

std::shared_ptr<gbox::ShaderProgram> gbox::Core::register_shader_program(std::string _shader_program_name, std::vector<std::string> _shader_files)
{
  std::vector<std::shared_ptr<gbox::Shader>> shaders;
  for (auto shader_file : _shader_files)
  {
    shaders.push_back(register_shader(shader_file));
  }

  if (m_shader_programs.find(_shader_program_name) == m_shader_programs.end())
  {
    std::shared_ptr<gbox::ShaderProgram> shader_program = std::make_shared<gbox::ShaderProgram>(shaders);
    m_shader_programs[_shader_program_name] = shader_program;
  }
  return m_shader_programs[_shader_program_name];
}

void gbox::Core::use_shader_program(std::string _shader_program_name)
{
  if (m_shader_programs.find(_shader_program_name) != m_shader_programs.end())
  {
    m_shader_programs[_shader_program_name]->use();
  }
}