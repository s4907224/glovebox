#ifndef GBOX_VERTEX_H
#define GBOX_VERTEX_H

#include <iostream>

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
      
  };// class Vertex
}// namespace gbox

#endif // GBOXVERTEXH