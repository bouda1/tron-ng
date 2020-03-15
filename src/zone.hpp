#ifndef _ZONE_HPP_
#define _ZONE_HPP_
#include "model.hpp"

class Zone : public Model {
 public:
  Zone(const std::string &name);
  const Model &get_model() const;
};

#endif
