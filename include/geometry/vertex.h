#ifndef GBOX_VERTEX_H
#define GBOX_VERTEX_H

#include <iostream>

#include "helpers/gl_utils.h"

namespace gbox
{
  class Vertex
  {
    public:
      // dtor
      ~Vertex();
      // ctor
      Vertex();
      // copy ctor
      Vertex(const Vertex& _vertex_other);
      // copy assignment operator
      Vertex& operator=(const Vertex& _vertex_other);
      // move ctor
      Vertex(Vertex&& _vertex_other);
      // move assignment operator
      Vertex& operator=(Vertex&& _vertex_other);

    private:
      glm::vec3 m_position;
      glm::vec3 m_normal;
      glm::vec2 m_tex_coord;
      
  };// class Vertex
}// namespace gbox

#endif // GBOXVERTEXH