#include "geometry/mesh.h"

int gbox::Mesh::m_instance_counter = 0;

gbox::Mesh::Mesh(std::shared_ptr<gbox::VAO> _vao)
{
  m_ID = m_instance_counter++;
  init_matrices();

  m_vao = _vao;
  m_vao->register_mvp(m_mvp);

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for Mesh with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Mesh::~Mesh()
{
  m_vao->unregister_mvp(m_mvp);

  #ifdef DEBUG_PRINTS  
  std::cout<<"Dtor called for Mesh with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Mesh::Mesh(const Mesh& _mesh_other)
{
  m_ID = m_instance_counter++;
  init_matrices();

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for Mesh with ID "<<m_ID<<" and Mesh with ID "<<_mesh_other.m_ID<<'\n';
  #endif
}

gbox::Mesh& gbox::Mesh::operator=(const Mesh& _mesh_other)
{
  m_ID = _mesh_other.m_ID;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for Mesh with ID "<<m_ID<<" and Mesh with ID "<<_mesh_other.m_ID<<'\n';
  #endif
  
  return *this;
}

gbox::Mesh::Mesh(Mesh&& _mesh_other)
{
  m_ID = _mesh_other.m_ID;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for Mesh with ID "<<m_ID<<" and Mesh with ID "<<_mesh_other.m_ID<<'\n';
  #endif

  _mesh_other.m_ID = -1;
}

gbox::Mesh& gbox::Mesh::operator=(Mesh&& _mesh_other)
{
  m_ID = _mesh_other.m_ID;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for Mesh with ID "<<m_ID<<" and Mesh with ID "<<_mesh_other.m_ID<<'\n';
  #endif

  _mesh_other.m_ID = -1;
  return *this;
}

void gbox::Mesh::set_model_matrix(glm::mat4 _model_matrix)
{
  *m_model_matrix = _model_matrix;

  update_mvp();
}

void gbox::Mesh::set_view_matrix(glm::mat4 _view_matrix)
{
  *m_view_matrix = _view_matrix;

  update_mvp();
}

void gbox::Mesh::set_projection_matrix(glm::mat4 _projection_matrix)
{
  *m_projection_matrix = _projection_matrix;

  update_mvp();
}

void gbox::Mesh::translate(glm::vec3 _translation)
{
  *m_model_matrix = glm::translate(*m_model_matrix, _translation);
  
  update_mvp();
}

void gbox::Mesh::update_mvp()
{
  *m_mvp = (*m_projection_matrix) * (*m_view_matrix) * (*m_model_matrix);
}

void gbox::Mesh::init_matrices()
{
  m_model_matrix = std::make_shared<glm::mat4>(1.f);
  m_view_matrix = std::make_shared<glm::mat4>(1.f);
  m_projection_matrix = std::make_shared<glm::mat4>(1.f);

  m_mvp = std::make_shared<glm::mat4>(1.f);
}