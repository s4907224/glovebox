#include "helpers/gl_helper.h"

int gbox::GLHelper::m_instance_counter = 0;

gbox::GLHelper::GLHelper()
{
  m_ID = m_instance_counter++;
  std::cout<<"Ctor called for GLHelper with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
}

gbox::GLHelper::~GLHelper()
{
  std::cout<<"Dtor called for GLHelper with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
}

gbox::GLHelper::GLHelper(const GLHelper& _GLHelper_other)
{
  m_ID = m_instance_counter++;
  std::cout<<"Copy ctor called for GLHelper with ID "<<m_ID<<" and GLHelper with ID "<<_GLHelper_other.m_ID<<std::dec<<'\n';
}

gbox::GLHelper& gbox::GLHelper::operator=(const GLHelper& _GLHelper_other)
{
  m_ID = _GLHelper_other.m_ID;
  std::cout<<"Copy assignment called for GLHelper with ID "<<m_ID<<" and GLHelper with ID "<<_GLHelper_other.m_ID<<std::dec<<'\n';
  return *this;
}

gbox::GLHelper::GLHelper(GLHelper&& _GLHelper_other)
{
  m_ID = _GLHelper_other.m_ID;
  std::cout<<"Move ctor called for GLHelper with ID "<<m_ID<<" and GLHelper with ID "<<_GLHelper_other.m_ID<<std::dec<<'\n';
  _GLHelper_other.m_ID = -1;
}

gbox::GLHelper& gbox::GLHelper::operator=(GLHelper&& _GLHelper_other)
{
  m_ID = _GLHelper_other.m_ID;
  std::cout<<"Move assignment called for GLHelper with ID "<<m_ID<<" and GLHelper with ID "<<_GLHelper_other.m_ID<<std::dec<<'\n';
  _GLHelper_other.m_ID = -1;
  return *this;
}