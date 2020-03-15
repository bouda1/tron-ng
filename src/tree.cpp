#include "tree.hpp"

Tree::Tree(const std::vector<size_t> &indices,
           const std::vector<glm::vec3> &vertices) {
  glm::vec3 v;
  size_t count = 0;
  size_t pos = 0;
  for (size_t i : indices) {
    v += vertices[i];
    count++;
    if (count == 3) {
      // Division by 3 for the average...
      v /= 3.0f;
      //insert({v.x, {v.y, {v.z, pos}}});
      count = 0;
      v = {0.0f, 0.0f, 0.0f};
      pos++;
    }
  }
}
