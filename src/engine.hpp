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
