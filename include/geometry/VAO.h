#ifndef GBOX_VAO_H
#define GBOX_VAO_H

#include <iostream>
#include <vector>
#include <string>

#include "helpers/gl_utils.h"
#include "geometry/vertex.h"

namespace gbox
{
  class VAO
  {
    public:
      // dtor
      ~VAO();
      // ctor
      VAO(std::string _file_path);
      // copy ctor
      VAO(const VAO& _vao_other);
      // copy assignment operator
      VAO& operator=(const VAO& _vao_other);
      // move ctor
      VAO(VAO&& _vao_other);
      // move assignment operator
      VAO& operator=(VAO&& _vao_other);
      // property for ID
      const int& ID() {return m_ID;}

      void draw();

    private:
      static int m_instance_counter;
      int m_ID;

      GLuint m_VAO_id;
      GLuint m_VBO_id;

      void create_VAO();
  };// class VAO
}// namespace gbox

#endif // GBOXVAOH