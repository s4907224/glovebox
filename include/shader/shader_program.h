#ifndef GBOX_SHADERPROGRAM_H
#define GBOX_SHADERPROGRAM_H

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
      ShaderProgram(std::string _vert, std::string _frag);

      ShaderProgram(std::vector<std::string> _shader_paths);

      ShaderProgram(std::vector<std::pair<std::string, GLenum> >_shader_data);

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

      std::vector<std::string> m_shader_file_paths;

      std::vector<std::shared_ptr<gbox::Shader>> compile_shaders(std::vector<std::string> _shader_paths);
      std::vector<std::shared_ptr<gbox::Shader>> compile_shaders(std::vector<std::pair<std::string, GLenum>> _shader_data);
      void link(std::vector<std::shared_ptr<gbox::Shader>>_shaders);
  };// class ShaderProgram
}// namespace gbox

#endif // GBOXSHADERPROGRAMH