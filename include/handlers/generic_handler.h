#ifndef GBOX_GenericHandler_H
#define GBOX_GenericHandler_H

#include <iostream>
#include <memory>

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

      bool quit_requested() const;

      const gbox::KeyHandler& get_key_handler();

    protected:
      static int m_instance_counter;
      int m_ID;

      virtual bool init_window() {return false;};

      bool m_quit;

      std::shared_ptr<gbox::KeyHandler> m_key_handler;
  };// class GenericHandler
}// namespace gbox

#endif // GBOXGenericHandlerH