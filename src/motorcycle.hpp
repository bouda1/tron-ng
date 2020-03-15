#ifndef _MOTORCYCLE_HPP_
#define _MOTORCYCLE_HPP_
#include "model.hpp"
#include "physics.hpp"

class Motorcycle : public Model {
  Physics _physics;

 public:
  Motorcycle();
  const Physics &getPhysics() const;
};

#endif
