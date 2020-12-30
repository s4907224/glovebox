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
      Vertex(glm::vec3 _position, glm::vec3 _normal, glm::vec2 _tex_coord);
      Vertex(glm::vec3 _position, glm::vec3 _normal);
      Vertex(glm::vec3 _position, glm::vec2 _tex_coord);
      Vertex(glm::vec3 _position);
      // copy ctor
      Vertex(const Vertex& _vertex_other);
      // copy assignment operator
      Vertex& operator=(const Vertex& _vertex_other);
      // move ctor
      Vertex(Vertex&& _vertex_other);
      // move assignment operator
      Vertex& operator=(Vertex&& _vertex_other);

      glm::vec3 m_position

    private:
      glm::vec3 m_position;
      glm::vec3 m_normal;
      glm::vec2 m_tex_coord;
      
  };// class Vertex
}// namespace gbox

#endif // GBOXVERTEXH