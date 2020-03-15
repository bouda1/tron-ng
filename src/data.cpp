#include "data.hpp"

Data::Data() : _v{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f} {}

Data::Data(float v0, float v1, float v2, float v3, float v4, float v5, float v6)
    : _v{v0, v1, v2, v3, v4, v5, v6} {}

Data::Data(const glm::vec3 &P, const glm::quat &q)
    : _v{P[0], P[1], P[2], q.x, q.y, q.z, q.w} {}

Data Data::operator*(float t) {
  return Data{_v[0] * t, _v[1] * t, _v[2] * t, _v[3] * t,
              _v[4] * t, _v[5] * t, _v[6] * t};
}

Data Data::operator+(const Data &d) {
  return Data{_v[0] + d._v[0], _v[1] + d._v[1], _v[2] + d._v[2],
              _v[3] + d._v[3], _v[4] + d._v[4], _v[5] + d._v[5],
              _v[6] + d._v[6]};
}
