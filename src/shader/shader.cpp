#include "shader/shader.h"

int gbox::Shader::m_instance_counter = 0;

gbox::Shader::Shader(std::string _file_path, GLenum _shader_type) :
  m_file_path(_file_path),
  m_shader_type(_shader_type),
  m_compiled(false)
{
  m_ID = m_instance_counter++;

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for Shader with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Shader::Shader(std::string _file_path) :
  m_file_path(_file_path),
  m_compiled(false)
{
  m_ID = m_instance_counter++;

  if (m_file_path.substr(m_file_path.find_last_of(".") + 1) == "frag")
  {
    m_shader_type = GL_FRAGMENT_SHADER;
  }
  else
  {
    m_shader_type = GL_VERTEX_SHADER;
  }

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for Shader with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Shader::~Shader()
{
  glDeleteShader(m_shader_id);

  #ifdef DEBUG_PRINTS  
  std::cout<<"Dtor called for Shader with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Shader::Shader(const Shader& _shader_other)
{
  m_ID = m_instance_counter++;

  m_file_path = _shader_other.m_file_path;
  m_shader_id = _shader_other.m_shader_id;
  m_shader_type = _shader_other.m_shader_type;
  m_compiled = _shader_other.m_compiled;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for Shader with ID "<<m_ID<<" and Shader with ID "<<_shader_other.m_ID<<'\n';
  #endif
}

gbox::Shader& gbox::Shader::operator=(const Shader& _shader_other)
{
  m_ID = _shader_other.m_ID;

  m_file_path = _shader_other.m_file_path;
  m_shader_id = _shader_other.m_shader_id;
  m_shader_type = _shader_other.m_shader_type;
  m_compiled = _shader_other.m_compiled;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for Shader with ID "<<m_ID<<" and Shader with ID "<<_shader_other.m_ID<<'\n';
  #endif
  
  return *this;
}

gbox::Shader::Shader(Shader&& _shader_other)
{
  m_ID = _shader_other.m_ID;

  m_file_path = _shader_other.m_file_path;
  m_shader_id = _shader_other.m_shader_id;
  m_shader_type = _shader_other.m_shader_type;
  m_compiled = _shader_other.m_compiled;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for Shader with ID "<<m_ID<<" and Shader with ID "<<_shader_other.m_ID<<'\n';
  #endif

  _shader_other.m_ID = -1;
}

gbox::Shader& gbox::Shader::operator=(Shader&& _shader_other)
{
  m_ID = _shader_other.m_ID;

  m_file_path = _shader_other.m_file_path;
  m_shader_id = _shader_other.m_shader_id;
  m_shader_type = _shader_other.m_shader_type;
  m_compiled = _shader_other.m_compiled;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for Shader with ID "<<m_ID<<" and Shader with ID "<<_shader_other.m_ID<<'\n';
  #endif

  _shader_other.m_ID = -1;
  return *this;
}

const GLuint& gbox::Shader::get_shader_ID() const
{
  return m_shader_id;
}

void gbox::Shader::compile()
{
  if(m_compiled)
  {
    return;
  }

  std::ifstream shader_file(m_file_path);
  std::string shader_contents((std::istreambuf_iterator<char>(shader_file)), 
  std::istreambuf_iterator<char>());
  const char* shader_data = shader_contents.c_str();

  m_shader_id = glCreateShader(m_shader_type);

  glShaderSource(m_shader_id, 1, &shader_data, NULL);
  glCompileShader(m_shader_id);

  int success;
  char infoLog[512];
  glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(m_shader_id, 512, NULL, infoLog);
    std::cout << "ERROR: SHADER COMPILATION FAILED (" <<m_file_path << ")\n" << infoLog <<'\n';
  }
  m_compiled = true;
}