#ifndef GBOX_MESH_H
#define GBOX_MESH_H

#include <iostream>

namespace gbox
{
  class Mesh
  {
    public:
      // dtor
      ~Mesh();
      // ctor
      Mesh();
      // copy ctor
      Mesh(const Mesh& _mesh_other);
      // copy assignment operator
      Mesh& operator=(const Mesh& _mesh_other);
      // move ctor
      Mesh(Mesh&& _mesh_other);
      // move assignment operator
      Mesh& operator=(Mesh&& _mesh_other);
      // property for ID
      const int& ID() {return m_ID;}

    private:
      static int m_instance_counter;
      int m_ID;
  };// class Mesh
}// namespace gbox

#endif // GBOXMESHH