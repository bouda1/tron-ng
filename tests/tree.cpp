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
#include "tree.hpp"
#include "gtest/gtest.h"
#include "data.hpp"

TEST(TreeZone, test) {
  int i = 1;
  ASSERT_EQ(i, 1);
}

TEST(DataTest, MultFloat) {
    Data d{1, 2, 3, 4, 5, 6, 7};
    d = d * 2;
    Data d1{2, 4, 6, 8, 10, 12, 14};
    ASSERT_EQ(d, d1);
}

TEST(DataTest, PlusEqual) {
    Data d{1, 2, 3, 4, 5, 6, 7};
    Data d1{2, 3, 4, 5, 6, 7, 8};
    d1 += d;
    Data d2{3, 5, 7, 9, 11, 13, 15};
    ASSERT_EQ(d1, d2);
}
