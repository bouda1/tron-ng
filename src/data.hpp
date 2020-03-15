#ifndef _DATA_HPP_
#define _DATA_HPP_
#include <glm/ext/quaternion_float.hpp>

class Data {
  float _v[7];

 public:
   Data();
   Data(float v0, float v1, float v2, float v3, float v4, float v5, float v6);
   Data(const glm::vec3 &P, const glm::quat &q);
   Data operator*(float t);
   Data operator+(const Data& d);
};

#endif

