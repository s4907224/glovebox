#include "handlers/sdl_gbox.h"

int gbox::SDLgbox::m_instance_counter = 0;

gbox::SDLgbox::SDLgbox()
{
  m_ID = m_instance_counter++;
  std::cout<<"Ctor called for SDLgbox with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::SDLgbox::~SDLgbox()
{
  std::cout<<"Dtor called for SDLgbox with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::SDLgbox::SDLgbox(const SDLgbox& _SDLgbox_other)
{
  m_ID = m_instance_counter++;
  std::cout<<"Copy ctor called for SDLgbox with ID "<<m_ID<<" and SDLgbox with ID "<<_SDLgbox_other.m_ID<<'\n';
}

gbox::SDLgbox& gbox::SDLgbox::operator=(const SDLgbox& _SDLgbox_other)
{
  m_ID = _SDLgbox_other.m_ID;
  std::cout<<"Copy assignment called for SDLgbox with ID "<<m_ID<<" and SDLgbox with ID "<<_SDLgbox_other.m_ID<<'\n';
  return *this;
}

gbox::SDLgbox::SDLgbox(SDLgbox&& _SDLgbox_other)
{
  m_ID = _SDLgbox_other.m_ID;
  std::cout<<"Move ctor called for SDLgbox with ID "<<m_ID<<" and SDLgbox with ID "<<_SDLgbox_other.m_ID<<'\n';
  _SDLgbox_other.m_ID = -1;
}

gbox::SDLgbox& gbox::SDLgbox::operator=(SDLgbox&& _SDLgbox_other)
{
  m_ID = _SDLgbox_other.m_ID;
  std::cout<<"Move assignment called for SDLgbox with ID "<<m_ID<<" and SDLgbox with ID "<<_SDLgbox_other.m_ID<<'\n';
  _SDLgbox_other.m_ID = -1;
  return *this;
}