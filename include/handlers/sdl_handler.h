#ifndef GBOX_SDLgbox_H
#define GBOX_SDLgbox_H

#define DEBUG_PRINTS

#include <iostream>
#include "helpers/gl_utils.h"
#include <SDL.h>
#include <SDL_mixer.h>

#include "handlers/generic_handler.h"

namespace gbox
{
  class SDLHandler : public GenericHandler
  {
    public:
      // dtor
      ~SDLHandler();
      // ctor
      SDLHandler();
      // copy ctor
      SDLHandler(const SDLHandler& _SDLgbox_other);
      // copy assignment operator
      SDLHandler& operator=(const SDLHandler& _SDLgbox_other);
      // move ctor
      SDLHandler(SDLHandler&& _SDLgbox_other);
      // move assignment operator
      SDLHandler& operator=(SDLHandler&& _SDLgbox_other);
      // property for ID
      const int& ID() {return m_ID;}

      void update();
      
      bool toggle_fullscreen();
      void enter_fullscreen();
      void exit_fullscreen();

    private:
      static int m_instance_counter;
      int m_ID;

      bool init_window();

      void handle_resize();

      SDL_Window* m_window;
      SDL_GLContext m_context;
  };// class SDLHandler
}// namespace gbox

#endif // GBOXSDLgboxH