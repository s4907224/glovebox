#include "core/core.h"

int gbox::Core::m_instance_counter = 0;

gbox::Core::Core()
{
  m_ID = m_instance_counter++;
  m_handler = std::make_shared<gbox::GenericHandler>();
  m_helper = std::make_shared<gbox::GLHelper>();
  std::cout<<"Ctor called for Core with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
}

gbox::Core::~Core()
{
  std::cout<<"Dtor called for Core with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
}

gbox::Core::Core(const Core& _core_other)
{
  m_ID = m_instance_counter++;
  m_handler = _core_other.m_handler;
  m_helper = _core_other.m_helper;
  std::cout<<"Copy ctor called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<std::dec<<'\n';
}

gbox::Core& gbox::Core::operator=(const Core& _core_other)
{
  m_ID = _core_other.m_ID;
  m_handler = _core_other.m_handler;
  m_helper = _core_other.m_helper;
  std::cout<<"Copy assignment called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<std::dec<<'\n';
  return *this;
}

gbox::Core::Core(Core&& _core_other)
{
  m_ID = _core_other.m_ID;
  m_handler = _core_other.m_handler;
  m_helper = _core_other.m_helper;
  std::cout<<"Move ctor called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<std::dec<<'\n';
  _core_other.m_ID = -1;
}

gbox::Core& gbox::Core::operator=(Core&& _core_other)
{
  m_ID = _core_other.m_ID;
  m_handler = _core_other.m_handler;
  m_helper = _core_other.m_helper;
  std::cout<<"Move assignment called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<std::dec<<'\n';
  _core_other.m_ID = -1;
  return *this;
}

void gbox::Core::register_SDL_handler()
{
  m_handler = std::make_shared<gbox::SDLHandler>();
}

void gbox::Core::update()
{
  std::cout<<"KEYCODES: ";
  m_handler->update();
  for (std::shared_ptr<gbox::KeyState> keystate: m_handler->get_key_handler().get_active_keys())
  {
    std::cout<<'['<<keystate->keycode<<"]\t";
  }
  std::cout<<'\n';
}

void gbox::Core::start_main_loop()
{
  while (!m_handler->quit_requested())
  {
    update();
  }
}