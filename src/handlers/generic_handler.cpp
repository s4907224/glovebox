#include "handlers/generic_handler.h"

int gbox::GenericHandler::m_instance_counter = 0;

gbox::GenericHandler::GenericHandler() :
  m_quit(false),
  m_key_handler(std::make_shared<gbox::KeyHandler>())
{
  m_ID = m_instance_counter++;
  std::cout<<"Ctor called for GenericHandler with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
}

gbox::GenericHandler::~GenericHandler()
{
  std::cout<<"Dtor called for GenericHandler with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
}

gbox::GenericHandler::GenericHandler(const GenericHandler& _GenericHandler_other)
{
  m_ID = m_instance_counter++;
  std::cout<<"Copy ctor called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<std::dec<<'\n';
}

gbox::GenericHandler& gbox::GenericHandler::operator=(const GenericHandler& _GenericHandler_other)
{
  m_ID = _GenericHandler_other.m_ID;
  std::cout<<"Copy assignment called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<std::dec<<'\n';
  return *this;
}

gbox::GenericHandler::GenericHandler(GenericHandler&& _GenericHandler_other)
{
  m_ID = _GenericHandler_other.m_ID;
  std::cout<<"Move ctor called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<std::dec<<'\n';
  _GenericHandler_other.m_ID = -1;
}

gbox::GenericHandler& gbox::GenericHandler::operator=(GenericHandler&& _GenericHandler_other)
{
  m_ID = _GenericHandler_other.m_ID;
  std::cout<<"Move assignment called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<std::dec<<'\n';
  _GenericHandler_other.m_ID = -1;
  return *this;
}

bool gbox::GenericHandler::quit_requested() const
{
  return m_quit;
}

const gbox::KeyHandler& gbox::GenericHandler::get_key_handler()
{
  return *m_key_handler;
}