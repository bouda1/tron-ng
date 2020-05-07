/*
 * Copyright (C) 2020 David Boucher
 * This file is part of tron-ng <https://github.com/bouda1/tron-ng>.
 *
 * tron-ng is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * tron-ng is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with tron-ng.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "data.hpp"
#include <cstring>

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

float* Data::ptr(uint32_t index) {
    return &_v[index];
}

Data& Data::operator+=(const Data &d) {
    auto v = _v.begin();
    auto vv = d._v.begin();
    while (v != _v.end()) {
        *v += *vv;
        ++v;
        ++vv;
    }
    return *this;
}

bool Data::operator==(const Data& other) const {
    return memcmp(_v.data(), other._v.data(), _v.size() * sizeof(float)) == 0;
}
