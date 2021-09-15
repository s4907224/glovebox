#include "camera/perspective_camera.h"

int gbox::PerspectiveCamera::m_instance_counter = 0;

gbox::PerspectiveCamera::PerspectiveCamera()
{
  m_ID = m_instance_counter++;

  update_projection_matrix();
  update_view_projection_matrix();

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for PerspectiveCamera with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::PerspectiveCamera::~PerspectiveCamera()
{
  #ifdef DEBUG_PRINTS  
  std::cout<<"Dtor called for PerspectiveCamera with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera& _perspectivecamera_other)
{
  m_ID = m_instance_counter++;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for PerspectiveCamera with ID "<<m_ID<<" and PerspectiveCamera with ID "<<_perspectivecamera_other.m_ID<<'\n';
  #endif
}

gbox::PerspectiveCamera& gbox::PerspectiveCamera::operator=(const PerspectiveCamera& _perspectivecamera_other)
{
  m_ID = _perspectivecamera_other.m_ID;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for PerspectiveCamera with ID "<<m_ID<<" and PerspectiveCamera with ID "<<_perspectivecamera_other.m_ID<<'\n';
  #endif
  
  return *this;
}

gbox::PerspectiveCamera::PerspectiveCamera(PerspectiveCamera&& _perspectivecamera_other)
{
  m_ID = _perspectivecamera_other.m_ID;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for PerspectiveCamera with ID "<<m_ID<<" and PerspectiveCamera with ID "<<_perspectivecamera_other.m_ID<<'\n';
  #endif

  _perspectivecamera_other.m_ID = -1;
}

gbox::PerspectiveCamera& gbox::PerspectiveCamera::operator=(PerspectiveCamera&& _perspectivecamera_other)
{
  m_ID = _perspectivecamera_other.m_ID;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for PerspectiveCamera with ID "<<m_ID<<" and PerspectiveCamera with ID "<<_perspectivecamera_other.m_ID<<'\n';
  #endif

  _perspectivecamera_other.m_ID = -1;
  return *this;
}

void gbox::PerspectiveCamera::update_projection_matrix()
{
  m_view_projection_dirty = true;
  m_projection = glm::perspective(glm::radians(90.f), 4.0f / 3.0f, 0.1f, 100.0f);
}