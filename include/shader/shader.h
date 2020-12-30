#ifndef GBOX_SHADER_H
#define GBOX_SHADER_H

#define DEBUG_PRINTS

#include <iostream>
#include <string>

#include "helpers/gl_utils.h"

namespace gbox
{
  class Shader
  {
    public:
      // dtor
      ~Shader();
      // ctor
      Shader(std::string _file_path, GLenum _shader_type);
      Shader(std::string _file_path);
      // copy ctor
      Shader(const Shader& _shader_other);
      // copy assignment operator
      Shader& operator=(const Shader& _shader_other);
      // move ctor
      Shader(Shader&& _shader_other);
      // move assignment operator
      Shader& operator=(Shader&& _shader_other);
      // property for ID
      const int& ID() {return m_ID;}

      const GLuint& get_shader_ID() const;

      void compile();

    private:
      static int m_instance_counter;
      int m_ID;

      std::string m_file_path;
      GLuint m_shader_id;
      GLenum m_shader_type;
  };// class Shader
}// namespace gbox

#endif // GBOXSHADERH