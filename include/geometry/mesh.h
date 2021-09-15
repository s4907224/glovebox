#ifndef GBOX_MESH_H
#define GBOX_MESH_H

#include <iostream>
#include "helpers/gl_utils.h"
#include "shader/shader_program.h"
#include "camera/camera.h"

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

      void set_model_matrix(glm::mat4 _model_matrix);
      void set_camera(std::shared_ptr<gbox::Camera> _camera);

      std::shared_ptr<glm::mat4> get_model_matrix() const;
      std::shared_ptr<glm::mat4> get_mvp() const;
      std::shared_ptr<glm::mat4> update_mvp();

      void translate(glm::vec3 _translation);
      void set_tranlation(glm::vec3 _translation);

      void set_shader_program(std::shared_ptr<gbox::ShaderProgram> _shader_program);
      std::shared_ptr<gbox::ShaderProgram> get_shader_program() const;


    private:
      static int m_instance_counter;
      int m_ID;

      std::shared_ptr<glm::mat4> m_model_matrix;
      std::shared_ptr<gbox::Camera> m_camera;

      std::shared_ptr<glm::mat4> m_mvp;

      std::shared_ptr<gbox::ShaderProgram> m_shader_program;

      

      void init_matrices();
  };// class Mesh
}// namespace gbox

#endif // GBOXMESHH