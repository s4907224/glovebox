#include "geometry/mesh.h"

int gbox::Mesh::m_instance_counter = 0;

gbox::Mesh::Mesh()
{
  m_ID = m_instance_counter++;

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for Mesh with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Mesh::~Mesh()
{
  #ifdef DEBUG_PRINTS  
  std::cout<<"Dtor called for Mesh with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Mesh::Mesh(const Mesh& _mesh_other)
{
  m_ID = m_instance_counter++;

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