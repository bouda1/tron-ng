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
#include "physics.hpp"
#include "data.hpp"
#include <array>
#include <cstring>
#include <glm/common.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <vector>

Physics::Physics() noexcept
    : _pos{0, 0, 0}, _M{500}, _P{0, 0, 0}, _fw{-1.0f, 0.0f, -0.3f, 0.0f},
      _rw{1.0f, 0.0f, -0.3f, 0.0f}, _model(1.0f) {}

void Physics::applyForce(const glm::vec3 &force) noexcept {}

void Physics::computeNextStep(float deltat) noexcept {
  Data data{_P, _q};
  // We store F = diff(_P)
  glm::vec3 v = _Ffw + _Frw + _M * glm::vec3(0, 0, -9.8);
  // We have _P at time t and F=diff(_P) at time t. We can then compute _P at
  // t + dt

  glm::vec3 fw{_model * _fw};
  glm::vec3 rw{_model * _rw};
  glm::vec3 tau = glm::cross(fw, _Ffw) + glm::cross(rw, _Frw);

  // We store diff(_q)
  glm::quat q = 0.5f * glm::quat(0.0f, _omega) * _q;

  Data diff(v, q);
  Data new_data = data + diff * deltat;
}

glm::mat4 const &Physics::getModel() const { return _model; }
