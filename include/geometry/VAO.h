#ifndef GBOX_VAO_H
#define GBOX_VAO_H

#include <iostream>
#include "helpers/gl_utils.h"

namespace gbox
{
  class VAO
  {
    public:
      // dtor
      ~VAO();
      // ctor
      VAO();
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

      glm::mat4 m_model_matrix;

      void create_VAO();
  };// class VAO
}// namespace gbox

#endif // GBOXVAOH