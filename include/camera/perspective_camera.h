#ifndef GBOX_PERSPECTIVECAMERA_H
#define GBOX_PERSPECTIVECAMERA_H

#include <iostream>

#include "camera/camera.h"

namespace gbox
{
  class PerspectiveCamera : public Camera
  {
    public:
      // dtor
      ~PerspectiveCamera();
      // ctor
      PerspectiveCamera();
      // copy ctor
      PerspectiveCamera(const PerspectiveCamera& _perspectivecamera_other);
      // copy assignment operator
      PerspectiveCamera& operator=(const PerspectiveCamera& _perspectivecamera_other);
      // move ctor
      PerspectiveCamera(PerspectiveCamera&& _perspectivecamera_other);
      // move assignment operator
      PerspectiveCamera& operator=(PerspectiveCamera&& _perspectivecamera_other);
      // property for ID
      const int& ID() {return m_ID;}

    private:
      static int m_instance_counter;
      int m_ID;

      void update_projection_matrix();
  };// class PerspectiveCamera
}// namespace gbox

#endif // GBOXPERSPECTIVECAMERAH