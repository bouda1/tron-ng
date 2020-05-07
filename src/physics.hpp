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
#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include <glm/detail/type_quat.hpp>
#include <glm/glm.hpp>

class Physics {
  // Position of G in the global coordinates
  glm::vec3 _pos;

  // Mass of the motorcycle
  const glm::float32 _M;
  // Linear moment of the motorcycle P = M * Vg wheree  M is the motorcycle
  // mass and Vg is the center of mass coordinates in the universe coordinates.
  glm::vec3 _P;

  // The motorcycle is defined with several objects:
  // * the motorcycle body
  // * the front wheel
  // * the rear wheel

  // Coordinates of wheels centers relatively to the motorcycle.
  const glm::vec4 _fw;
  // The force on the front wheel in the universe coordinates
  glm::vec3 _Ffw;
  const glm::vec4 _rw;
  // The force on the rear wheel in the universe coordinates
  glm::vec3 _Frw;

  // Rotation of the solid as a quaternion
  glm::quat _q;

  // Inertia tensor inverse
  glm::mat3 _I_1;

  // Angular speed
  glm::vec3 _omega;

  // Total angular moment
  glm::mat3 _L;

  // Model position
  glm::mat4 _model;

public:
  Physics() noexcept;
  void applyForce(const glm::vec3 &force) noexcept;
  void computeNextStep(float deltat) noexcept;
  glm::mat4 const &getModel();
  constexpr glm::float32 mass() { return _M; }
};
#endif
