#ifndef GBOX_GENERIC_HANDLER_H
#define GBOX_GENERIC_HANDLER_H

#include <iostream>

namespace gbox
{
  class Generic_handler
  {
    public:
      // dtor
      ~Generic_handler();
      // ctor
      Generic_handler();
      // copy ctor
      Generic_handler(const Generic_handler& _generic_handler_other);
      // copy assignment operator
      Generic_handler& operator=(const Generic_handler& _generic_handler_other);
      // move ctor
      Generic_handler(Generic_handler&& _generic_handler_other);
      // move assignment operator
      Generic_handler& operator=(Generic_handler&& _generic_handler_other);
      // property for ID
      const int& ID() {return m_ID;}

    private:
      static int m_instance_counter;
      int m_ID;
  };// class Generic_handler
}// namespace gbox

#endif // GBOXGENERIC_HANDLERH