#ifndef GBOX_CAMERA_H
#define GBOX_CAMERA_H

#include <iostream>
#include <memory>

#include "helpers/gl_utils.h"

namespace gbox
{
  class Camera
  {
    public:
      // dtor
      virtual ~Camera() = default;
      // ctor
      Camera();
      // copy ctor
      Camera(const Camera& _camera_other);
      // copy assignment operator
      Camera& operator=(const Camera& _camera_other);
      // move ctor
      Camera(Camera&& _camera_other);
      // move assignment operator
      Camera& operator=(Camera&& _camera_other);
      // property for ID
      const int& ID() {return m_ID;}

      std::shared_ptr<glm::mat4> get_view_projection_matrix() const;
      void update_view_projection_matrix();
      bool update_performed() const;

      void add_pitch(float _pitch);
      void add_yaw(float _yaw);
      void translate(glm::vec3 _translation);
      void view_space_translate(glm::vec3 _translation);

    protected:
      static int m_instance_counter;
      int m_ID;

      glm::vec3 m_position;

      glm::vec3 m_forward_vector;
      glm::vec3 m_right_vector;
      glm::vec3 m_up_vector;
      
      glm::vec3 m_global_up_vector;
      
      glm::mat4 m_projection;
      glm::mat4 m_view;

      std::shared_ptr<glm::mat4> m_view_projection;

      bool m_view_projection_dirty = true;
      bool m_update_performed = true;

      void calculate_up_vector();
      void calculate_right_vector();

      void update_view_matrix();
      virtual void update_projection_matrix() {};
  };// class Camera
}// namespace gbox

#endif // GBOX_CAMERA_H
