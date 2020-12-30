#ifndef GBOX_VAO_H
#define GBOX_VAO_H

#include <iostream>
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

      bool m_vert_data_is_dynamic;

      // std::vector<gbox::Vertex> m_vertex_data;

      void load_from_obj(std::string _obj_file_path);

      void create_VAO();
  };// class VAO
}// namespace gbox

#endif // GBOXVAOH