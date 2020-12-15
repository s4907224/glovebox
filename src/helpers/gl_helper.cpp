#include "helpers/gl_helper.h"

int gbox::Gl_helper::m_instance_counter = 0;

gbox::Gl_helper::Gl_helper()
{
  m_ID = m_instance_counter++;
  std::cout<<"Ctor called for Gl_helper with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::Gl_helper::~Gl_helper()
{
  std::cout<<"Dtor called for Gl_helper with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::Gl_helper::Gl_helper(const Gl_helper& _gl_helper_other)
{
  m_ID = m_instance_counter++;
  std::cout<<"Copy ctor called for Gl_helper with ID "<<m_ID<<" and Gl_helper with ID "<<_gl_helper_other.m_ID<<'\n';
}

gbox::Gl_helper& gbox::Gl_helper::operator=(const Gl_helper& _gl_helper_other)
{
  m_ID = _gl_helper_other.m_ID;
  std::cout<<"Copy assignment called for Gl_helper with ID "<<m_ID<<" and Gl_helper with ID "<<_gl_helper_other.m_ID<<'\n';
  return *this;
}

gbox::Gl_helper::Gl_helper(Gl_helper&& _gl_helper_other)
{
  m_ID = _gl_helper_other.m_ID;
  std::cout<<"Move ctor called for Gl_helper with ID "<<m_ID<<" and Gl_helper with ID "<<_gl_helper_other.m_ID<<'\n';
  _gl_helper_other.m_ID = -1;
}

gbox::Gl_helper& gbox::Gl_helper::operator=(Gl_helper&& _gl_helper_other)
{
  m_ID = _gl_helper_other.m_ID;
  std::cout<<"Move assignment called for Gl_helper with ID "<<m_ID<<" and Gl_helper with ID "<<_gl_helper_other.m_ID<<'\n';
  _gl_helper_other.m_ID = -1;
  return *this;
}