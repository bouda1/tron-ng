#ifndef _TREE_HPP_
#define _TREE_HPP_
#include <glm/glm.hpp>
#include <map>
#include <vector>

class Tree : public std::map<float, std::map<float, std::map<float, size_t>>> {
public:
  Tree(const std::vector<size_t> &indices,
       const std::vector<glm::vec3> &vertices);
};

#endif
