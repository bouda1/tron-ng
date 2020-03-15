#ifndef _TREE_HPP_
#define _TREE_HPP_
#include <deque>
#include <map>

class ZonePoint {
public:
  ZonePoint(float x, float y, float z, short index)
      : x(x), y(y), z(z), index(index) {}
  float x, y, z;
  short index;
};

class ZoneTree {
  std::deque<ZonePoint> _zp;
  std::multimap<float, ZonePoint *> _x;
  std::multimap<float, ZonePoint *> _y;
  std::multimap<float, ZonePoint *> _z;

public:
  void insert(float x, float y, float z, short idx);
};

#endif
