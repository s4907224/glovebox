#ifndef GBOX_GenericHandler_H
#define GBOX_GenericHandler_H

#include <iostream>
#include <memory>
#include <array>

#include "helpers/gl_utils.h"

#include "user_io/key_handler.h"

namespace gbox
{
  class GenericHandler
  {
    public:
      // dtor
      virtual ~GenericHandler() = 0;
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

      virtual void update() = 0;

      virtual bool toggle_fullscreen() = 0;
      virtual void enter_fullscreen() = 0;
      virtual void exit_fullscreen() = 0;

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

      virtual bool init_window() = 0;

      virtual void handle_resize() =0;
      void resize_gl();
  };// class GenericHandler
}// namespace gbox

#endif // GBOXGenericHandlerH