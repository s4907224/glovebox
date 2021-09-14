#include "shader/shader_program.h"

int gbox::ShaderProgram::m_instance_counter = 0;

gbox::ShaderProgram::ShaderProgram(std::string _vert, std::string _frag)
{
  m_ID = m_instance_counter++;

  std::vector<std::shared_ptr<gbox::Shader>> shaders = compile_shaders({_vert, _frag});
  link(shaders);

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for ShaderProgram with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::ShaderProgram::ShaderProgram(std::vector<std::pair<std::string, GLenum>> _shader_data)
{
  m_ID = m_instance_counter++;

  std::vector<std::shared_ptr<gbox::Shader>> shaders = compile_shaders(_shader_data);
  link(shaders);

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for ShaderProgram with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::ShaderProgram::ShaderProgram(std::vector<std::string> _shader_paths)
{
  m_ID = m_instance_counter++;

  std::vector<std::shared_ptr<gbox::Shader>> shaders = compile_shaders(_shader_paths);
  link(shaders);

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for ShaderProgram with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::ShaderProgram::ShaderProgram(std::vector<std::shared_ptr<gbox::Shader>>  _shaders)
{
  m_ID = m_instance_counter++;

  link(_shaders);

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
  m_shader_file_paths = _shaderprogram_other.m_shader_file_paths;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for ShaderProgram with ID "<<m_ID<<" and ShaderProgram with ID "<<_shaderprogram_other.m_ID<<'\n';
  #endif
}

gbox::ShaderProgram& gbox::ShaderProgram::operator=(const ShaderProgram& _shaderprogram_other)
{
  m_ID = _shaderprogram_other.m_ID;

  m_shader_program_id = _shaderprogram_other.m_shader_program_id;
  m_shader_file_paths = _shaderprogram_other.m_shader_file_paths;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for ShaderProgram with ID "<<m_ID<<" and ShaderProgram with ID "<<_shaderprogram_other.m_ID<<'\n';
  #endif
  
  return *this;
}

gbox::ShaderProgram::ShaderProgram(ShaderProgram&& _shaderprogram_other)
{
  m_ID = _shaderprogram_other.m_ID;

  m_shader_program_id = _shaderprogram_other.m_shader_program_id;
  m_shader_file_paths = _shaderprogram_other.m_shader_file_paths;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for ShaderProgram with ID "<<m_ID<<" and ShaderProgram with ID "<<_shaderprogram_other.m_ID<<'\n';
  #endif

  _shaderprogram_other.m_ID = -1;
}

gbox::ShaderProgram& gbox::ShaderProgram::operator=(ShaderProgram&& _shaderprogram_other)
{
  m_ID = _shaderprogram_other.m_ID;

  m_shader_program_id = _shaderprogram_other.m_shader_program_id;
  m_shader_file_paths = _shaderprogram_other.m_shader_file_paths;

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

std::vector<std::shared_ptr<gbox::Shader>> gbox::ShaderProgram::compile_shaders(std::vector<std::string> _shader_paths)
{
  std::vector<std::shared_ptr<gbox::Shader>>shaders;
  for (auto shader_path : _shader_paths)
  {
    shaders.push_back(std::make_shared<gbox::Shader>(shader_path));
    m_shader_file_paths.push_back(shader_path);
    shaders.back()->compile();
  }

  return shaders;
}

std::vector<std::shared_ptr<gbox::Shader>> gbox::ShaderProgram::compile_shaders(std::vector<std::pair<std::string, GLenum>> _shader_data)
{
  std::vector<std::shared_ptr<gbox::Shader>> shaders;
  for (auto shader_data : _shader_data)
  {
    shaders.push_back(std::make_shared<gbox::Shader>(shader_data.first, shader_data.second));
    m_shader_file_paths.push_back(shader_data.first);
    shaders.back()->compile();
  }

  return shaders;
}

void gbox::ShaderProgram::link(std::vector<std::shared_ptr<gbox::Shader>> _shaders)
{
  unsigned int shader_program;
  shader_program = glCreateProgram();

  for (auto shader : _shaders)
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