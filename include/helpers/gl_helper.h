#ifndef GBOX_GL_HELPER_H
#define GBOX_GL_HELPER_H

#include <iostream>

namespace gbox
{
  class Gl_helper
  {
    public:
      // dtor
      ~Gl_helper();
      // ctor
      Gl_helper();
      // copy ctor
      Gl_helper(const Gl_helper& _gl_helper_other);
      // copy assignment operator
      Gl_helper& operator=(const Gl_helper& _gl_helper_other);
      // move ctor
      Gl_helper(Gl_helper&& _gl_helper_other);
      // move assignment operator
      Gl_helper& operator=(Gl_helper&& _gl_helper_other);
      // property for ID
      const int& ID() {return m_ID;}

    private:
      static int m_instance_counter;
      int m_ID;
  };// class Gl_helper
}// namespace gbox

#endif // GBOXGL_HELPERH