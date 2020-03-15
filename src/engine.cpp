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
      /* The computation should be done every step ms */
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

void Engine::_compute() {}

const std::vector<std::unique_ptr<Motorcycle>> &Engine::getMotorcycles() const {
  return _motorcycles;
}
