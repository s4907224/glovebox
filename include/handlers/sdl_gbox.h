#ifndef GBOX_SDLgbox_H
#define GBOX_SDLgbox_H

#include <iostream>

#include "handlers/generic_handler.h"

namespace gbox
{
  class SDLgbox : public GenericHandler
  {
    public:
      // dtor
      ~SDLgbox();
      // ctor
      SDLgbox();
      // copy ctor
      SDLgbox(const SDLgbox& _SDLgbox_other);
      // copy assignment operator
      SDLgbox& operator=(const SDLgbox& _SDLgbox_other);
      // move ctor
      SDLgbox(SDLgbox&& _SDLgbox_other);
      // move assignment operator
      SDLgbox& operator=(SDLgbox&& _SDLgbox_other);
      // property for ID
      const int& ID() {return m_ID;}

    private:
      static int m_instance_counter;
      int m_ID;
  };// class SDLgbox
}// namespace gbox

#endif // GBOXSDLgboxH