#ifndef GBOX_CORE_H
#define GBOX_CORE_H

#include <iostream>
#include <memory>

#include "handlers/generic_handler.h"
#include "handlers/sdl_handler.h"
#include "user_io/key_handler.h"
#include "helpers/gl_helper.h"

namespace gbox
{
  class Core
  {
    public:
      // dtor
      ~Core();
      // ctor
      Core();
      // copy ctor
      Core(const Core& _core_other);
      // copy assignment operator
      Core& operator=(const Core& _core_other);
      // move ctor
      Core(Core&& _core_other);
      // move assignment operator
      Core& operator=(Core&& _core_other);
      // property for ID
      const int& ID() {return m_ID;}

      void register_SDL_handler();
      void register_SDL_handler(std::shared_ptr<gbox::SDLHandler> _sdl_handler);

      void start_main_loop();

      bool quit_requested();

    private:
      static int m_instance_counter;
      int m_ID;

      std::shared_ptr<gbox::GenericHandler> m_handler;
      std::shared_ptr<gbox::GLHelper> m_helper;
      std::shared_ptr<gbox::KeyHandler> m_key_handler;

      void update();
  };// class Core
}// namespace gbox

#endif // GBOXCOREH