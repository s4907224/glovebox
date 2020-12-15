#include "core/core.h"

int gbox::Core::m_instance_counter = 0;

gbox::Core::Core()
{
  m_ID = m_instance_counter++;
  m_handler = std::make_shared<gbox::Generic_handler>();
  std::cout<<"Ctor called for Core with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::Core::~Core()
{
  std::cout<<"Dtor called for Core with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::Core::Core(const Core& _core_other)
{
  m_ID = m_instance_counter++;
  m_handler = _core_other.m_handler;
  std::cout<<"Copy ctor called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<'\n';
}

gbox::Core& gbox::Core::operator=(const Core& _core_other)
{
  m_ID = _core_other.m_ID;
  m_handler = _core_other.m_handler;
  std::cout<<"Copy assignment called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<'\n';
  return *this;
}

gbox::Core::Core(Core&& _core_other)
{
  m_ID = _core_other.m_ID;
  m_handler = _core_other.m_handler;
  std::cout<<"Move ctor called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<'\n';
  _core_other.m_ID = -1;
}

gbox::Core& gbox::Core::operator=(Core&& _core_other)
{
  m_ID = _core_other.m_ID;
  m_handler = _core_other.m_handler;
  std::cout<<"Move assignment called for Core with ID "<<m_ID<<" and Core with ID "<<_core_other.m_ID<<'\n';
  _core_other.m_ID = -1;
  return *this;
}