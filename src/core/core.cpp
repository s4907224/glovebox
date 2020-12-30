#include "core/core.h"

int gbox::Core::m_instance_counter = 0;

gbox::Core::Core()
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

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<std::dec<<'\n';
  #endif
}

gbox::Core& gbox::Core::operator=(const Core& _core_other)
{
  m_ID = _core_other.m_ID;
  m_handler = _core_other.m_handler;
  m_key_handler = _core_other.m_key_handler;

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

  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<std::dec<<'\n';
  #endif

  _core_other.m_ID = -1;
  return *this;
}

void gbox::Core::register_SDL_handler()
{
  m_handler = std::make_shared<gbox::SDLHandler>();
}

void gbox::Core::update()
{
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
          break;
        }
      }
    }
  }
}

void gbox::Core::start_main_loop()
{
  m_handler->register_keybind(GBSC_F, GBIND_fullscreen_toggle);
  m_handler->register_keybind(GBSC_escape, GBIND_exit);
  m_handler->set_borderless_fullscreen(true);

  init_GL();

  std::string vert_path = "shaders/basic/flat_colour.vert";
  std::string frag_path = "shaders/basic/flat_colour.frag";

  gbox::ShaderProgram prog(vert_path, frag_path);
  prog.use();

  m_VAOs.push_back(std::make_shared<gbox::VAO>());

  while (!m_handler->quit_requested())
  {
    update();
    draw();
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