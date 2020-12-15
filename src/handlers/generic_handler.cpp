#include "handlers/generic_handler.h"

int gbox::Generic_handler::m_instance_counter = 0;

gbox::Generic_handler::Generic_handler()
{
  m_ID = m_instance_counter++;
  std::cout<<"Ctor called for Generic_handler with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::Generic_handler::~Generic_handler()
{
  std::cout<<"Dtor called for Generic_handler with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::Generic_handler::Generic_handler(const Generic_handler& _generic_handler_other)
{
  m_ID = m_instance_counter++;
  std::cout<<"Copy ctor called for Generic_handler with ID "<<m_ID<<" and Generic_handler with ID "<<_generic_handler_other.m_ID<<'\n';
}

gbox::Generic_handler& gbox::Generic_handler::operator=(const Generic_handler& _generic_handler_other)
{
  m_ID = _generic_handler_other.m_ID;
  std::cout<<"Copy assignment called for Generic_handler with ID "<<m_ID<<" and Generic_handler with ID "<<_generic_handler_other.m_ID<<'\n';
  return *this;
}

gbox::Generic_handler::Generic_handler(Generic_handler&& _generic_handler_other)
{
  m_ID = _generic_handler_other.m_ID;
  std::cout<<"Move ctor called for Generic_handler with ID "<<m_ID<<" and Generic_handler with ID "<<_generic_handler_other.m_ID<<'\n';
  _generic_handler_other.m_ID = -1;
}

gbox::Generic_handler& gbox::Generic_handler::operator=(Generic_handler&& _generic_handler_other)
{
  m_ID = _generic_handler_other.m_ID;
  std::cout<<"Move assignment called for Generic_handler with ID "<<m_ID<<" and Generic_handler with ID "<<_generic_handler_other.m_ID<<'\n';
  _generic_handler_other.m_ID = -1;
  return *this;
}