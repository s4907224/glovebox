#ifndef GBOX_MESH_H
#define GBOX_MESH_H

#include <iostream>
#include "helpers/gl_utils.h"
#include "geometry/VAO.h"

namespace gbox
{
  class VAO;

  class Mesh
  {
    public:
      // dtor
      ~Mesh();
      // ctor
      Mesh(std::shared_ptr<gbox::VAO> _vao);
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

      void set_model_matrix(glm::mat4 _model_matrix);
      void set_view_matrix(glm::mat4 _view_matrix);
      void set_projection_matrix(glm::mat4 _projection_matrix);

      void translate(glm::vec3 _translation);

    private:
      static int m_instance_counter;
      int m_ID;

      std::shared_ptr<glm::mat4> m_model_matrix;
      std::shared_ptr<glm::mat4> m_view_matrix;
      std::shared_ptr<glm::mat4> m_projection_matrix;

      std::shared_ptr<glm::mat4> m_mvp;

      void update_mvp();

      void init_matrices();

      std::shared_ptr<gbox::VAO> m_vao;
  };// class Mesh
}// namespace gbox

#endif // GBOXMESHH