#ifndef _PHYSICS_HPP_
#define _PHYSICS_HPP_

#include <glm/detail/type_quat.hpp>
#include <glm/glm.hpp>

class Physics {
  // Position of G in the global coordinates
  glm::vec3 _pos;

  // Mass of the motorcycle
  const float _M;
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
  glm::mat4 const &getModel() const;
};
#endif
