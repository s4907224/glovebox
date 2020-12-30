#include "geometry/vertex.h"

gbox::Vertex::Vertex()
{
  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for Vertex @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Vertex::~Vertex()
{
  #ifdef DEBUG_PRINTS  
  std::cout<<"Dtor called for Vertex @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Vertex::Vertex(const Vertex& _vertex_other)
{
  m_position = _vertex_other.m_position;
  m_normal = _vertex_other.m_normal;
  m_tex_coord = _vertex_other.m_normal;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for Vertex and Vertex\n";
  #endif
}

gbox::Vertex& gbox::Vertex::operator=(const Vertex& _vertex_other)
{
  m_position = _vertex_other.m_position;
  m_normal = _vertex_other.m_normal;
  m_tex_coord = _vertex_other.m_normal;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for Vertex\n";
  #endif
  
  return *this;
}

gbox::Vertex::Vertex(Vertex&& _vertex_other)
{
  m_position = _vertex_other.m_position;
  m_normal = _vertex_other.m_normal;
  m_tex_coord = _vertex_other.m_normal;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for Vertex and Vertex\n";
  #endif
}

gbox::Vertex& gbox::Vertex::operator=(Vertex&& _vertex_other)
{
  m_position = _vertex_other.m_position;
  m_normal = _vertex_other.m_normal;
  m_tex_coord = _vertex_other.m_normal;
  
  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for Vertex and Vertex\n";
  #endif

  return *this;
}