#include "user_io/key_handler.h"

int gbox::KeyHandler::m_instance_counter = 0;

gbox::KeyHandler::KeyHandler()
{
  m_ID = m_instance_counter++;

  #ifdef DEBUG_PRINTS  
  std::cout<<"Ctor called for KeyHandler with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif

 flush_keystates();
}

gbox::KeyHandler::~KeyHandler()
{
  #ifdef DEBUG_PRINTS
  std::cout<<"Dtor called for KeyHandler with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::KeyHandler::KeyHandler(const KeyHandler& _keyhandler_other)
{
  m_ID = m_instance_counter++;
  m_keystates = _keyhandler_other.m_keystates;
  m_active_keys = _keyhandler_other.m_active_keys;
  m_keybinds = _keyhandler_other.m_keybinds;

  #ifdef DEBUG_PRINTS  
  std::cout<<"Copy ctor called for KeyHandler with ID "<<m_ID<<" and KeyHandler with ID "<<_keyhandler_other.m_ID<<std::dec<<'\n';
  #endif
}

gbox::KeyHandler& gbox::KeyHandler::operator=(const KeyHandler& _keyhandler_other)
{
  m_ID = _keyhandler_other.m_ID;
  m_keystates = _keyhandler_other.m_keystates;
  m_active_keys = _keyhandler_other.m_active_keys;
  m_keybinds = _keyhandler_other.m_keybinds;

  #ifdef DEBUG_PRINTS  
  std::cout<<"Copy assignment called for KeyHandler with ID "<<m_ID<<" and KeyHandler with ID "<<_keyhandler_other.m_ID<<std::dec<<'\n';
  #endif

  return *this;
}

gbox::KeyHandler::KeyHandler(KeyHandler&& _keyhandler_other)
{
  m_ID = _keyhandler_other.m_ID;
  m_keystates = _keyhandler_other.m_keystates;
  m_active_keys = _keyhandler_other.m_active_keys;
  m_keybinds = _keyhandler_other.m_keybinds;

  #ifdef DEBUG_PRINTS  
  std::cout<<"Move ctor called for KeyHandler with ID "<<m_ID<<" and KeyHandler with ID "<<_keyhandler_other.m_ID<<std::dec<<'\n';
  #endif

  _keyhandler_other.m_ID = -1;
}

gbox::KeyHandler& gbox::KeyHandler::operator=(KeyHandler&& _keyhandler_other)
{
  m_ID = _keyhandler_other.m_ID;
  m_keystates = _keyhandler_other.m_keystates;
  m_active_keys = _keyhandler_other.m_active_keys;
  m_keybinds = _keyhandler_other.m_keybinds;

  #ifdef DEBUG_PRINTS  
  std::cout<<"Move assignment called for KeyHandler with ID "<<m_ID<<" and KeyHandler with ID "<<_keyhandler_other.m_ID<<std::dec<<'\n';
  #endif

  _keyhandler_other.m_ID = -1;
  return *this;
}

void gbox::KeyHandler::flush_keystates()
{
  for (int i = 0; i < GBSCANCODE_MAX_VAL + 1; i++)
  {
    m_keystates[i] = std::make_shared<gbox::KeyState>();
    m_keystates[i]->scancode = i;
  }
}

void gbox::KeyHandler::press_key(int _scancode)
{
  m_keystates[_scancode]->just_released = false;
  m_keystates[_scancode]->just_pressed = !m_keystates[_scancode]->pressed;
  m_keystates[_scancode]->pressed = true;
  m_active_keys.insert(_scancode);
}

void gbox::KeyHandler::release_key(int _scancode)
{
  m_keystates[_scancode]->just_pressed = false;
  m_keystates[_scancode]->just_released = m_keystates[_scancode]->pressed;
  m_keystates[_scancode]->pressed = false;
}

void gbox::KeyHandler::update()
{
  for(std::shared_ptr<gbox::KeyState>& keystate: m_keystates)
  {
    keystate->just_pressed = false;
    keystate->just_released = false;

    if(!keystate->pressed)
    {
      m_active_keys.erase(keystate->scancode);
    }
  }
}

std::vector<std::shared_ptr<gbox::KeyState>> gbox::KeyHandler::get_active_keys() const
{
  std::vector<std::shared_ptr<gbox::KeyState>> active_keys;

  for(int scancode : m_active_keys)
  {
    active_keys.push_back(m_keystates[scancode]);
  }

  return active_keys;
}

void gbox::KeyHandler::register_keybind(int _scancode, int _keybind)
{
  m_keybinds[_scancode].insert(_keybind);
}

std::set<int> gbox::KeyHandler::get_keybinds(int _scancode) const
{
  return m_keybinds[_scancode];
}