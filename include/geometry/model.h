#ifndef GBOX_MODEL_H
#define GBOX_MODEL_H

#include <iostream>
#include "geometry/VAO.h"

namespace gbox
{
  class Model
  {
    public:
      // dtor
      ~Model();
      // ctor
      Model();
      // copy ctor
      Model(const Model& _model_other);
      // copy assignment operator
      Model& operator=(const Model& _model_other);
      // move ctor
      Model(Model&& _model_other);
      // move assignment operator
      Model& operator=(Model&& _model_other);
      // property for ID
      const int& ID() {return m_ID;}

    private:
      static int m_instance_counter;
      int m_ID;
  };// class Model
}// namespace gbox

#endif // GBOXMODELH