#include "user_io/key_handler.h"

int gbox::KeyHandler::m_instance_counter = 0;

gbox::KeyHandler::KeyHandler()
{
  m_ID = m_instance_counter++;
  std::cout<<"Ctor called for KeyHandler with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';

  for (int i = 0; i < GBKC_right_gui + 1; i++)
  {
    m_keystates[i] = std::make_shared<gbox::KeyState>();
    m_keystates[i]->keycode = i;
  }
}

gbox::KeyHandler::~KeyHandler()
{
  std::cout<<"Dtor called for KeyHandler with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
}

gbox::KeyHandler::KeyHandler(const KeyHandler& _keyhandler_other)
{
  m_ID = m_instance_counter++;
  std::cout<<"Copy ctor called for KeyHandler with ID "<<m_ID<<" and KeyHandler with ID "<<_keyhandler_other.m_ID<<std::dec<<'\n';
}

gbox::KeyHandler& gbox::KeyHandler::operator=(const KeyHandler& _keyhandler_other)
{
  m_ID = _keyhandler_other.m_ID;
  std::cout<<"Copy assignment called for KeyHandler with ID "<<m_ID<<" and KeyHandler with ID "<<_keyhandler_other.m_ID<<std::dec<<'\n';
  return *this;
}

gbox::KeyHandler::KeyHandler(KeyHandler&& _keyhandler_other)
{
  m_ID = _keyhandler_other.m_ID;
  std::cout<<"Move ctor called for KeyHandler with ID "<<m_ID<<" and KeyHandler with ID "<<_keyhandler_other.m_ID<<std::dec<<'\n';
  _keyhandler_other.m_ID = -1;
}

gbox::KeyHandler& gbox::KeyHandler::operator=(KeyHandler&& _keyhandler_other)
{
  m_ID = _keyhandler_other.m_ID;
  std::cout<<"Move assignment called for KeyHandler with ID "<<m_ID<<" and KeyHandler with ID "<<_keyhandler_other.m_ID<<std::dec<<'\n';
  _keyhandler_other.m_ID = -1;
  return *this;
}

void gbox::KeyHandler::flush_keystates()
{
  std::cout<<"Flush Keystates\n";
  for (auto &keystate: m_keystates)
  {
    std::cout<<"process keystates\n";
    keystate->just_pressed = false;
    keystate->just_released = false;
    keystate->just_released = false;
  }
}

void gbox::KeyHandler::press_key(int _keycode)
{
  std::cout<<"Pressing key with keycode: "<<_keycode<<'\n';
  m_keystates[_keycode]->just_released = false;
  m_keystates[_keycode]->just_pressed = !m_keystates[_keycode]->pressed;
  m_keystates[_keycode]->pressed = true;
  m_active_keys.insert(_keycode);
}

void gbox::KeyHandler::release_key(int _keycode)
{
  m_keystates[_keycode]->just_pressed = false;
  m_keystates[_keycode]->just_released = m_keystates[_keycode]->pressed;
  m_keystates[_keycode]->pressed = false;
}

void gbox::KeyHandler::update()
{
  for(std::shared_ptr<gbox::KeyState>& keystate: m_keystates)
  {
    keystate->just_pressed = false;
    keystate->just_released = false;

    if(!keystate->pressed)
    {
      m_active_keys.erase(keystate->keycode);
    }
  }
}

std::vector<std::shared_ptr<gbox::KeyState>> gbox::KeyHandler::get_active_keys() const
{
  std::vector<std::shared_ptr<gbox::KeyState>> active_keys;

  for(int keycode : m_active_keys)
  {
    active_keys.push_back(m_keystates[keycode]);
  }

  return active_keys;
}