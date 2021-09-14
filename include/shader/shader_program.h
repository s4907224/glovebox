#ifndef GBOX_SHADERPROGRAM_H
#define GBOX_SHADERPROGRAM_H

#define DEBUG_PRINTS

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "helpers/gl_utils.h"
#include "shader/shader.h"

namespace gbox
{
  class ShaderProgram
  {
    public:
      // dtor
      ~ShaderProgram();
      // ctor
      ShaderProgram(std::vector<std::shared_ptr<gbox::Shader>> _shaders);
      // copy ctor
      ShaderProgram(const ShaderProgram& _shaderprogram_other);
      // copy assignment operator
      ShaderProgram& operator=(const ShaderProgram& _shaderprogram_other);
      // move ctor
      ShaderProgram(ShaderProgram&& _shaderprogram_other);
      // move assignment operator
      ShaderProgram& operator=(ShaderProgram&& _shaderprogram_other);
      // property for ID
      const int& ID() {return m_ID;}

      const GLuint& get_program_ID() const;

      void use() const;

    private:
      static int m_instance_counter;
      int m_ID;

      GLuint m_shader_program_id;

      std::vector<std::shared_ptr<gbox::Shader>> m_shaders;

      void link();
  };// class ShaderProgram
}// namespace gbox

#endif // GBOXSHADERPROGRAMH