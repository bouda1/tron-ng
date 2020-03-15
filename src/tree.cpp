#include "tree.hpp"

void ZoneTree::insert(float x, float y, float z, short idx) {
  auto& zp = _zp.emplace_back(x, y, z, idx);
  _x.emplace(x, &zp);
  _y.emplace(y, &zp);
  _z.emplace(z, &zp);
}
