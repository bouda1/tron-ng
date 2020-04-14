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
#include "engine.hpp"
#include "motorcycle.hpp"
#include "zone.hpp"
#include <chrono>
#include <iostream>

Engine::Engine(uint32_t step) : _step(step), _stop(false) {
  _thread = std::thread([this] {
    auto start = std::chrono::high_resolution_clock::now();
    for (;;) {
      std::cout << "start = "
                << std::chrono::time_point_cast<std::chrono::milliseconds>(
                       std::chrono::high_resolution_clock::now())
                       .time_since_epoch()
                       .count()
                << "\n";
      start += std::chrono::milliseconds(_step);
      /* The computation should be done every _step_ ms */
      _compute();
      if (_stop)
        break;
      std::this_thread::sleep_until(start);
    }
  });
}

Engine::~Engine() noexcept {
  _stop = true;
  _thread.join();
}

void Engine::setZone(Zone *zone) { _zone.reset(zone); }

Zone const *Engine::getZone() const { return _zone.get(); }

void Engine::addMotorcycle(Motorcycle *motorcycle) {
  _motorcycles.emplace_back(motorcycle);
}

void Engine::_compute() {
}

const std::vector<std::unique_ptr<Motorcycle>> &Engine::getMotorcycles() const {
  return _motorcycles;
}
