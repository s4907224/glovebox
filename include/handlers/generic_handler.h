#ifndef GBOX_GenericHandler_H
#define GBOX_GenericHandler_H

#include <iostream>

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

      virtual void draw() {};

      bool quit_requested() const;

    protected:
      static int m_instance_counter;
      int m_ID;

      virtual bool init_window() {return false;};

      bool m_quit;
  };// class GenericHandler
}// namespace gbox

#endif // GBOXGenericHandlerH