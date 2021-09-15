#include "camera/camera.h"

int gbox::Camera::m_instance_counter = 0;

gbox::Camera::Camera()
{
  m_ID = m_instance_counter++;

  m_view_projection = std::make_shared<glm::mat4>(1.f);
  m_position = {0.f, 0.f, 0.f};

  m_global_up_vector = glm::vec3(0.f, 1.f, 0.f);
  m_forward_vector = glm::vec3(0.f, 0.f, 1.f);
  calculate_right_vector();
  calculate_up_vector();

  update_view_matrix();

  #ifdef DEBUG_PRINTS
  std::cout<<"Ctor called for Camera with ID "<<m_ID<<" @"<<std::hex<<this<<std::dec<<'\n';
  #endif
}

gbox::Camera::Camera(const Camera& _camera_other)
{
  m_ID = m_instance_counter++;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy ctor called for Camera with ID "<<m_ID<<" and Camera with ID "<<_camera_other.m_ID<<'\n';
  #endif
}

gbox::Camera& gbox::Camera::operator=(const Camera& _camera_other)
{
  m_ID = _camera_other.m_ID;

  #ifdef DEBUG_PRINTS
  std::cout<<"Copy assignment called for Camera with ID "<<m_ID<<" and Camera with ID "<<_camera_other.m_ID<<'\n';
  #endif
  
  return *this;
}

gbox::Camera::Camera(Camera&& _camera_other)
{
  m_ID = _camera_other.m_ID;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move ctor called for Camera with ID "<<m_ID<<" and Camera with ID "<<_camera_other.m_ID<<'\n';
  #endif

  _camera_other.m_ID = -1;
}

gbox::Camera& gbox::Camera::operator=(Camera&& _camera_other)
{
  m_ID = _camera_other.m_ID;

  #ifdef DEBUG_PRINTS
  std::cout<<"Move assignment called for Camera with ID "<<m_ID<<" and Camera with ID "<<_camera_other.m_ID<<'\n';
  #endif

  _camera_other.m_ID = -1;
  return *this;
}

std::shared_ptr<glm::mat4> gbox::Camera::get_view_projection_matrix() const
{
  return m_view_projection;
}

void gbox::Camera::add_pitch(float _pitch)
{
  m_forward_vector = glm::rotate(m_forward_vector, _pitch, m_right_vector);
  
  calculate_right_vector();
  calculate_up_vector();
  update_view_matrix();
}

void gbox::Camera::add_yaw(float _yaw)
{
  m_forward_vector = glm::rotate(m_forward_vector, _yaw, m_global_up_vector);

  calculate_right_vector();
  calculate_up_vector();
  update_view_matrix();
}

void gbox::Camera::translate(glm::vec3 _translation)
{
  m_position += _translation;
  update_view_matrix();
}

void gbox::Camera::view_space_translate(glm::vec3 _translation)
{
  glm::vec3 view_space_translation = m_forward_vector * _translation.z + m_right_vector * _translation.x + m_up_vector * _translation.y;
  m_position += view_space_translation;

  update_view_matrix();
}

void gbox::Camera::calculate_right_vector()
{
  m_right_vector = glm::cross(m_forward_vector, m_global_up_vector); 
}

void gbox::Camera::calculate_up_vector()
{
  m_up_vector = glm::cross(m_right_vector, m_forward_vector);
}

void gbox::Camera::update_view_projection_matrix()
{
  if (not m_view_projection_dirty)
  {
    m_update_performed = false;
    return;
  }

  *m_view_projection = m_projection * m_view;
  m_update_performed = true;
  m_view_projection_dirty = false;
}

void gbox::Camera::update_view_matrix()
{
  m_view_projection_dirty = true;
  m_view = glm::lookAt(m_position, m_position + m_forward_vector, m_up_vector);
}

bool gbox::Camera::update_performed() const
{
  return m_update_performed;
}