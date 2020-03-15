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
#ifndef _ENGINE_HPP_
#define _ENGINE_HPP_
#include <atomic>
#include <thread>
#include <vector>

class Zone;
class Motorcycle;

class Engine {
  uint32_t _step;
  std::thread _thread;
  std::atomic_bool _stop;
  std::unique_ptr<Zone> _zone;
  std::vector<std::unique_ptr<Motorcycle>> _motorcycles;

  void _compute();

public:
  Engine(uint32_t step);
  ~Engine() noexcept;

  void setZone(Zone *zone);
  Zone const *getZone() const;
  void addMotorcycle(Motorcycle *motorcycle);
  std::vector<std::unique_ptr<Motorcycle>> const &getMotorcycles() const;
};

#endif
