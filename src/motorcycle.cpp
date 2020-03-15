#include "motorcycle.hpp"
#include "model.hpp"

Motorcycle::Motorcycle()
    : Model("/home/david/Projets/tron-ng/objects/motorcycle.obj"),
      _physics() {}

const Physics &Motorcycle::getPhysics() const { return _physics; }
