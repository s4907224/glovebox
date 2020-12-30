#include "geometry/vertex.h"

gbox::Vertex::Vertex(glm::vec3 _position, glm::vec3 _normal, glm::vec2 _tex_coord) :
  m_position(_position),
  m_normal(_normal),
  m_tex_coord(_tex_coord)
{
  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for Vertex @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Vertex::Vertex(glm::vec3 _position, glm::vec3 _normal) :
  m_position(_position),
  m_normal(_normal),
  m_tex_coord(0.f, 0.f)
{
  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for Vertex @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Vertex::Vertex(glm::vec3 _position, glm::vec2 _tex_coord) :
  m_position(_position),
  m_normal(0.f, 0.f, 1.f),
  m_tex_coord(_tex_coord)
{
  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for Vertex @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Vertex::Vertex(glm::vec3 _position) :
  m_position(_position),
  m_normal({0.f, 0.f, 1.f}),
  m_tex_coord(0.f, 0.f)
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