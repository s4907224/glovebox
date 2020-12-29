#include "handlers/generic_handler.h"

int gbox::GenericHandler::m_instance_counter = 0;

gbox::GenericHandler::GenericHandler() :
  m_quit(false),
  m_is_fullscreen(false),
  m_borderless(false),
  m_key_handler(std::make_shared<gbox::KeyHandler>())
{
  m_ID = m_instance_counter++;

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for GenericHandler with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

// gbox::GenericHandler::~GenericHandler() {}

gbox::GenericHandler::~GenericHandler()
{
  #ifdef DEBUG_PRINTS
  std::cout<<"Dtor called for GenericHandler with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::GenericHandler::GenericHandler(const GenericHandler& _GenericHandler_other)
{
  m_ID = m_instance_counter++;
  m_quit = _GenericHandler_other.m_quit;
  m_is_fullscreen = _GenericHandler_other.m_is_fullscreen;
  m_borderless = _GenericHandler_other.m_borderless;
  m_resolution = _GenericHandler_other.m_resolution;
  m_alt_resolution = _GenericHandler_other.m_alt_resolution;
  m_display_resolution = _GenericHandler_other.m_display_resolution;
  m_windowed_position = _GenericHandler_other.m_windowed_position;
  m_key_handler = _GenericHandler_other.m_key_handler;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<std::dec<<'\n';
  #endif
}

gbox::GenericHandler& gbox::GenericHandler::operator=(const GenericHandler& _GenericHandler_other)
{
  m_ID = _GenericHandler_other.m_ID;
  m_quit = _GenericHandler_other.m_quit;
  m_is_fullscreen = _GenericHandler_other.m_is_fullscreen;
  m_borderless = _GenericHandler_other.m_borderless;
  m_resolution = _GenericHandler_other.m_resolution;
  m_alt_resolution = _GenericHandler_other.m_alt_resolution;
  m_display_resolution = _GenericHandler_other.m_display_resolution;
  m_windowed_position = _GenericHandler_other.m_windowed_position;
  m_key_handler = _GenericHandler_other.m_key_handler;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<std::dec<<'\n';
  #endif
  return *this;
}

gbox::GenericHandler::GenericHandler(GenericHandler&& _GenericHandler_other)
{
  m_ID = _GenericHandler_other.m_ID;
  m_quit = _GenericHandler_other.m_quit;
  m_is_fullscreen = _GenericHandler_other.m_is_fullscreen;
  m_borderless = _GenericHandler_other.m_borderless;
  m_resolution = _GenericHandler_other.m_resolution;
  m_alt_resolution = _GenericHandler_other.m_alt_resolution;
  m_display_resolution = _GenericHandler_other.m_display_resolution;
  m_windowed_position = _GenericHandler_other.m_windowed_position;
  m_key_handler = _GenericHandler_other.m_key_handler;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<std::dec<<'\n';
  #endif
  _GenericHandler_other.m_ID = -1;
}

gbox::GenericHandler& gbox::GenericHandler::operator=(GenericHandler&& _GenericHandler_other)
{
  m_ID = _GenericHandler_other.m_ID;
  m_quit = _GenericHandler_other.m_quit;
  m_is_fullscreen = _GenericHandler_other.m_is_fullscreen;
  m_borderless = _GenericHandler_other.m_borderless;
  m_resolution = _GenericHandler_other.m_resolution;
  m_alt_resolution = _GenericHandler_other.m_alt_resolution;
  m_display_resolution = _GenericHandler_other.m_display_resolution;
  m_windowed_position = _GenericHandler_other.m_windowed_position;
  m_key_handler = _GenericHandler_other.m_key_handler;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for GenericHandler with ID "<<m_ID<<" and GenericHandler with ID "<<_GenericHandler_other.m_ID<<std::dec<<'\n';
  #endif
  _GenericHandler_other.m_ID = -1;
  return *this;
}

bool gbox::GenericHandler::quit_requested() const
{
  return m_quit;
}

void gbox::GenericHandler::request_quit()
{
  m_quit = true;
}

const gbox::KeyHandler& gbox::GenericHandler::get_key_handler()
{
  return *m_key_handler;
}

std::array<int, 2> gbox::GenericHandler::get_resolution() const
{
  return m_resolution;
}

int gbox::GenericHandler::width() const
{
  return m_resolution[0];
}

int gbox::GenericHandler::height() const
{
  return m_resolution[1];
}

void gbox::GenericHandler::register_keybind(int _scancode, int _keybind)
{
  m_key_handler->register_keybind(_scancode, _keybind);
}

void gbox::GenericHandler::set_borderless_fullscreen(bool _borderless)
{
  m_borderless = _borderless;
}

void gbox::GenericHandler::resize_gl()
{
  glViewport(0, 0, width(), height());
  std::cout<<"Resized GL Viewport to ["<<width()<<'x'<<height()<<"]\n";
}