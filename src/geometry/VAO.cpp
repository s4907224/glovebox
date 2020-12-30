#include "geometry/VAO.h"

int gbox::VAO::m_instance_counter = 0;

gbox::VAO::VAO(std::string _file_path)
{
  m_ID = m_instance_counter++;

  create_VAO();

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for VAO with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::VAO::~VAO()
{
  glDeleteVertexArrays(1, &m_VAO_id);
  glDeleteBuffers(1, &m_VBO_id);

  #ifdef DEBUG_PRINTS  
  std::cout<<"Dtor called for VAO with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::VAO::VAO(const VAO& _vao_other)
{
  m_ID = m_instance_counter++;

  m_VAO_id = _vao_other.m_VAO_id;
  m_VBO_id = _vao_other.m_VBO_id;
  m_vert_data_is_dynamic = _vao_other.m_vert_data_is_dynamic;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for VAO with ID "<<m_ID<<" and VAO with ID "<<_vao_other.m_ID<<'\n';
  #endif
}

gbox::VAO& gbox::VAO::operator=(const VAO& _vao_other)
{
  m_ID = _vao_other.m_ID;

  m_VAO_id = _vao_other.m_VAO_id;
  m_VBO_id = _vao_other.m_VBO_id;
  m_vert_data_is_dynamic = _vao_other.m_vert_data_is_dynamic;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for VAO with ID "<<m_ID<<" and VAO with ID "<<_vao_other.m_ID<<'\n';
  #endif
  
  return *this;
}

gbox::VAO::VAO(VAO&& _vao_other)
{
  m_ID = _vao_other.m_ID;

  m_VAO_id = _vao_other.m_VAO_id;
  m_VBO_id = _vao_other.m_VBO_id;
  m_vert_data_is_dynamic = _vao_other.m_vert_data_is_dynamic;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for VAO with ID "<<m_ID<<" and VAO with ID "<<_vao_other.m_ID<<'\n';
  #endif

  _vao_other.m_ID = -1;
}

gbox::VAO& gbox::VAO::operator=(VAO&& _vao_other)
{
  m_ID = _vao_other.m_ID;

  m_VAO_id = _vao_other.m_VAO_id;
  m_VBO_id = _vao_other.m_VBO_id;
  m_vert_data_is_dynamic = _vao_other.m_vert_data_is_dynamic;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for VAO with ID "<<m_ID<<" and VAO with ID "<<_vao_other.m_ID<<'\n';
  #endif

  _vao_other.m_ID = -1;
  return *this;
}

void gbox::VAO::create_VAO()
{
  glGenVertexArrays(1, &m_VAO_id);
  glBindVertexArray(m_VAO_id);

  float vert_positions[9] =
  {
    -0.5f, -0.5f, 0.f,
      0.f,  0.5f, 0.f,
     0.5f, -0.5f, 0.f,
  };

  glGenBuffers(1, &m_VBO_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO_id);
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vert_positions, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void gbox::VAO::draw()
{
  glBindVertexArray(m_VAO_id);
  glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(3));
}

void gbox::VAO::load_from_obj()
{
  
}