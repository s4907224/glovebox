#ifndef GBOX_GLUTILS_H
#define GBOX_GLUTILS_H

#include <string>
#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace gbox
{
  unsigned int compile_shader(std::string _shader_source_file, GLenum _shader_type);

  unsigned int compile_basic_shader_program(std::string _vert_shader_source_file, std::string _frag_shader_source_file);

  unsigned int compile_frag_shader(std::string _frag_shader_source_file);

  unsigned int compile_vert_shader(std::string _vert_shader_source_file);
}// namespace gbox

#endif // GBOX_GLUTILS_H