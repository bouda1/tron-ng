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
#ifndef _DATA_HPP_
#define _DATA_HPP_
#include <glm/ext/quaternion_float.hpp>
#include <array>

class Data {
  std::array<float, 7> _v;

public:
  Data();
  Data(float v0, float v1, float v2, float v3, float v4, float v5, float v6);
  Data(const glm::vec3 &P, const glm::quat &q);
  Data operator*(float t);
  Data operator+(const Data &d);
  Data& operator+=(const Data &d);
  bool operator==(const Data &other) const;
  float* ptr(uint32_t index);
};

#endif
