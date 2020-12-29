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
  init_triangle_VAO();

  while (!m_handler->quit_requested())
  {
    update();
    draw();
  }
}

bool gbox::Core::init_GL()
{
  std::cout<<"Init GL\n";
  return true;
}

void gbox::Core::init_triangle_VAO()
{
  float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
  };

  shader_program = gbox::compile_basic_shader_program(
    "shaders/basic/flat_colour.vert",
    "shaders/basic/flat_colour.frag"
  );

  glGenVertexArraysAPPLE(1, &VAO);

  glGenBuffers(1, &VBO);

  glBindVertexArrayAPPLE(VAO); 

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}

void gbox::Core::draw()
{
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glBindVertexArrayAPPLE(VAO);
  glUseProgram(shader_program);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}