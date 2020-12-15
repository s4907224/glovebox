#include "handlers/sdl_gbox.h"

int gbox::SDL_gbox::m_instance_counter = 0;

gbox::SDL_gbox::SDL_gbox()
{
  m_ID = m_instance_counter++;
  std::cout<<"Ctor called for SDL_gbox with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::SDL_gbox::~SDL_gbox()
{
  std::cout<<"Dtor called for SDL_gbox with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::SDL_gbox::SDL_gbox(const SDL_gbox& _SDL_gbox_other)
{
  m_ID = m_instance_counter++;
  std::cout<<"Copy ctor called for SDL_gbox with ID "<<m_ID<<" and SDL_gbox with ID "<<_SDL_gbox_other.m_ID<<'\n';
}

gbox::SDL_gbox& gbox::SDL_gbox::operator=(const SDL_gbox& _SDL_gbox_other)
{
  m_ID = _SDL_gbox_other.m_ID;
  std::cout<<"Copy assignment called for SDL_gbox with ID "<<m_ID<<" and SDL_gbox with ID "<<_SDL_gbox_other.m_ID<<'\n';
  return *this;
}

gbox::SDL_gbox::SDL_gbox(SDL_gbox&& _SDL_gbox_other)
{
  m_ID = _SDL_gbox_other.m_ID;
  std::cout<<"Move ctor called for SDL_gbox with ID "<<m_ID<<" and SDL_gbox with ID "<<_SDL_gbox_other.m_ID<<'\n';
  _SDL_gbox_other.m_ID = -1;
}

gbox::SDL_gbox& gbox::SDL_gbox::operator=(SDL_gbox&& _SDL_gbox_other)
{
  m_ID = _SDL_gbox_other.m_ID;
  std::cout<<"Move assignment called for SDL_gbox with ID "<<m_ID<<" and SDL_gbox with ID "<<_SDL_gbox_other.m_ID<<'\n';
  _SDL_gbox_other.m_ID = -1;
  return *this;
}