#ifndef GBOX_GLHelper_H
#define GBOX_GLHelper_H

#include <iostream>

namespace gbox
{
  class GLHelper
  {
    public:
      // dtor
      ~GLHelper();
      // ctor
      GLHelper();
      // copy ctor
      GLHelper(const GLHelper& _GLHelper_other);
      // copy assignment operator
      GLHelper& operator=(const GLHelper& _GLHelper_other);
      // move ctor
      GLHelper(GLHelper&& _GLHelper_other);
      // move assignment operator
      GLHelper& operator=(GLHelper&& _GLHelper_other);
      // property for ID
      const int& ID() {return m_ID;}

    private:
      static int m_instance_counter;
      int m_ID;
  };// class GLHelper
}// namespace gbox

#endif // GBOXGLHelperH