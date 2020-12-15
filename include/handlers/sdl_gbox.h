#ifndef GBOX_SDL_gbox_H
#define GBOX_SDL_gbox_H

#include <iostream>

namespace gbox
{
  class SDL_gbox
  {
    public:
      // dtor
      ~SDL_gbox();
      // ctor
      SDL_gbox();
      // copy ctor
      SDL_gbox(const SDL_gbox& _SDL_gbox_other);
      // copy assignment operator
      SDL_gbox& operator=(const SDL_gbox& _SDL_gbox_other);
      // move ctor
      SDL_gbox(SDL_gbox&& _SDL_gbox_other);
      // move assignment operator
      SDL_gbox& operator=(SDL_gbox&& _SDL_gbox_other);
      // property for ID
      const int& ID() {return m_ID;}

    private:
      static int m_instance_counter;
      int m_ID;
  };// class SDL_gbox
}// namespace gbox

#endif // GBOXSDL_gboxH