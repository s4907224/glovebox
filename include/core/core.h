#ifndef GBOX_CORE_H
#define GBOX_CORE_H

#include <iostream>
#include <memory>

#include "handlers/generic_handler.h"

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

    private:
      static int m_instance_counter;
      int m_ID;

      std::shared_ptr<gbox::Generic_handler> m_handler;

  };// class Core
}// namespace gbox

#endif // GBOXCOREH