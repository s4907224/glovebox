#include "shader/shader_program.h"

int gbox::ShaderProgram::m_instance_counter = 0;

gbox::ShaderProgram::ShaderProgram(std::vector<std::shared_ptr<gbox::Shader>> _shaders) : m_shaders(_shaders)
{
  m_ID = m_instance_counter++;

  link();

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for ShaderProgram with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::ShaderProgram::~ShaderProgram()
{
  #ifdef DEBUG_PRINTS  
  std::cout<<"Dtor called for ShaderProgram with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::ShaderProgram::ShaderProgram(const ShaderProgram& _shaderprogram_other)
{
  m_ID = m_instance_counter++;

  m_shader_program_id = _shaderprogram_other.m_shader_program_id;
  m_shaders = _shaderprogram_other.m_shaders;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for ShaderProgram with ID "<<m_ID<<" and ShaderProgram with ID "<<_shaderprogram_other.m_ID<<'\n';
  #endif
}

gbox::ShaderProgram& gbox::ShaderProgram::operator=(const ShaderProgram& _shaderprogram_other)
{
  m_ID = _shaderprogram_other.m_ID;

  m_shader_program_id = _shaderprogram_other.m_shader_program_id;
  m_shaders = _shaderprogram_other.m_shaders;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for ShaderProgram with ID "<<m_ID<<" and ShaderProgram with ID "<<_shaderprogram_other.m_ID<<'\n';
  #endif
  
  return *this;
}

gbox::ShaderProgram::ShaderProgram(ShaderProgram&& _shaderprogram_other)
{
  m_ID = _shaderprogram_other.m_ID;

  m_shader_program_id = _shaderprogram_other.m_shader_program_id;
  m_shaders = _shaderprogram_other.m_shaders;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for ShaderProgram with ID "<<m_ID<<" and ShaderProgram with ID "<<_shaderprogram_other.m_ID<<'\n';
  #endif

  _shaderprogram_other.m_ID = -1;
}

gbox::ShaderProgram& gbox::ShaderProgram::operator=(ShaderProgram&& _shaderprogram_other)
{
  m_ID = _shaderprogram_other.m_ID;

  m_shader_program_id = _shaderprogram_other.m_shader_program_id;
  m_shaders = _shaderprogram_other.m_shaders;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for ShaderProgram with ID "<<m_ID<<" and ShaderProgram with ID "<<_shaderprogram_other.m_ID<<'\n';
  #endif

  _shaderprogram_other.m_ID = -1;
  return *this;
}

const GLuint& gbox::ShaderProgram::get_program_ID() const
{
  return m_shader_program_id;
}

void gbox::ShaderProgram::link()
{
  unsigned int shader_program;
  shader_program = glCreateProgram();

  for (auto shader : m_shaders)
  {
    glAttachShader(shader_program, shader->get_shader_ID());
  }
  glLinkProgram(shader_program);

  int success;
  char infoLog[512];
  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
    std::cout << "ERROR: SHADER PROGRAM CREATION FAILED\n" << infoLog <<'\n';
  }

  m_shader_program_id = shader_program;
}

void gbox::ShaderProgram::use() const
{
  glUseProgram(m_shader_program_id);
}