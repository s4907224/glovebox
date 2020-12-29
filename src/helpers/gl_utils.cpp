#include "helpers/gl_utils.h"

unsigned int gbox::compile_shader(std::string _shader_source_file, GLenum _shader_type)
{
  std::ifstream shader_file(_shader_source_file);
  std::string shader_contents((std::istreambuf_iterator<char>(shader_file)), 
  std::istreambuf_iterator<char>());
  const char* shader_data = shader_contents.c_str();

  unsigned int shader;
  shader = glCreateShader(_shader_type);

  glShaderSource(shader, 1, &shader_data, NULL);
  glCompileShader(shader);

  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::cout << "ERROR: SHADER COMPILATION FAILED (" <<_shader_source_file << ")\n" << infoLog <<'\n';
  }

  return shader;
}

unsigned int gbox::compile_basic_shader_program(std::string _vert_shader_source_file, std::string _frag_shader_source_file)
{
  unsigned int vert_shader = gbox::compile_vert_shader(_vert_shader_source_file);
  unsigned int frag_shader = gbox::compile_frag_shader(_frag_shader_source_file);

  unsigned int shader_program;
  shader_program = glCreateProgram();

  glAttachShader(shader_program, vert_shader);
  glAttachShader(shader_program, frag_shader);
  glLinkProgram(shader_program);

  int success;
  char infoLog[512];
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
    std::cout << "ERROR: SHADER PROGRAM CREATION FAILED\n" << infoLog <<'\n';
  }

  // glDeleteShader(vert_shader);
  // glDeleteShader(frag_shader);

  return shader_program;
}

unsigned int gbox::compile_frag_shader(std::string _frag_shader_source_file)
{
  return gbox::compile_shader(_frag_shader_source_file, GL_FRAGMENT_SHADER);
}

unsigned int gbox::compile_vert_shader(std::string _vert_shader_source_file)
{
  return gbox::compile_shader(_vert_shader_source_file, GL_VERTEX_SHADER);
}