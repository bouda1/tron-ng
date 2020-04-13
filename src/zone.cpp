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
#include "zone.hpp"

Zone::Zone(const std::string &name) : Model(name) {

  /* Construction of the rtree */
  float x1, x2, y1, y2, z1, z2;
  int count = 0;
  int triangle_id = 0;
  for (auto &i : _indices) {
    auto &v = _vertices[i];
    if (count == 0) {
      x1 = x2 = v[0];
      y1 = y2 = v[1];
      z1 = z2 = v[2];
      count++;
    } else {
      if (v[0] < x1)
        x1 = v[0];
      if (v[0] > x2)
        x2 = v[0];
      if (v[1] < y1)
        y1 = v[1];
      if (v[1] > y2)
        y2 = v[1];
      if (v[2] < z1)
        z1 = v[2];
      if (v[2] > z2)
        z2 = v[2];
      if (count == 2) {
        box b(point(x1, y1, z1), point(x2, y2, z2));
        _tree.insert(std::make_pair(b, triangle_id++));
        count = 0;
      } else
        count++;
    }
  }
}
