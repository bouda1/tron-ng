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
#ifndef _TREE_HPP_
#define _TREE_HPP_
#include <deque>
#include <map>

class ZonePoint {
public:

  float x, y, z;
  short index;

  ZonePoint(float x, float y, float z, short index)
      : x(x), y(y), z(z), index(index) {}
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
