#ifndef GBOX_GenericHandler_H
#define GBOX_GenericHandler_H

#include <iostream>
#include <memory>
#include <array>

#include "user_io/key_handler.h"

namespace gbox
{
  class GenericHandler
  {
    public:
      // dtor
      ~GenericHandler();
      // ctor
      GenericHandler();
      // copy ctor
      GenericHandler(const GenericHandler& _GenericHandler_other);
      // copy assignment operator
      GenericHandler& operator=(const GenericHandler& _GenericHandler_other);
      // move ctor
      GenericHandler(GenericHandler&& _GenericHandler_other);
      // move assignment operator
      GenericHandler& operator=(GenericHandler&& _GenericHandler_other);
      // property for ID
      const int& ID() {return m_ID;}

      virtual void update() {};

      virtual bool toggle_fullscreen() {return false;};
      virtual void enter_fullscreen() {};
      virtual void exit_fullscreen() {};

      bool quit_requested() const;
      void request_quit();

      const gbox::KeyHandler& get_key_handler();
      void register_keybind(int _scancode, int _keybind);

      std::array<int, 2> get_resolution() const;

      int width() const;
      int height() const;

      void set_borderless_fullscreen(bool _borderless);

    protected:
      static int m_instance_counter;
      int m_ID;

      bool m_quit;
      bool m_is_fullscreen;
      bool m_borderless;

      std::array<int, 2> m_resolution;
      std::array<int, 2> m_alt_resolution;
      std::array<int, 2> m_display_resolution;

      std::array<int, 2> m_windowed_position;

      std::shared_ptr<gbox::KeyHandler> m_key_handler;

      virtual bool init_window() {return false;};
  };// class GenericHandler
}// namespace gbox

#endif // GBOXGenericHandlerH