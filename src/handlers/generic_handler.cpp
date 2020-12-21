#include "handlers/generic_handler.h"

int gbox::GenericHandler::m_instance_counter = 0;

gbox::GenericHandler::GenericHandler() : m_quit(false)
{
  m_ID = m_instance_counter++;
  std::cout<<"Ctor called for GenericHandler with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::GenericHandler::~GenericHandler()
{
  std::cout<<"Dtor called for GenericHandler with ID "<<m_ID<<" @"<<std::hex<<this<<'\n';
}

gbox::GenericHandler::GenericHandler(const GenericHandler& _GenericHandler_other)
{
  m_ID = m_instance_counter++;
  std::cout<<"Copy ctor called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<'\n';
}

gbox::GenericHandler& gbox::GenericHandler::operator=(const GenericHandler& _GenericHandler_other)
{
  m_ID = _GenericHandler_other.m_ID;
  std::cout<<"Copy assignment called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<'\n';
  return *this;
}

gbox::GenericHandler::GenericHandler(GenericHandler&& _GenericHandler_other)
{
  m_ID = _GenericHandler_other.m_ID;
  std::cout<<"Move ctor called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<'\n';
  _GenericHandler_other.m_ID = -1;
}

gbox::GenericHandler& gbox::GenericHandler::operator=(GenericHandler&& _GenericHandler_other)
{
  m_ID = _GenericHandler_other.m_ID;
  std::cout<<"Move assignment called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<'\n';
  _GenericHandler_other.m_ID = -1;
  return *this;
}

bool gbox::GenericHandler::quit_requested() const
{
  return m_quit;
}