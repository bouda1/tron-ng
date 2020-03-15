#ifndef _MODEL_HPP_
#define _MODEL_HPP_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Model {
  std::vector<glm::vec3> _vertices;
  std::vector<glm::vec3> _colors;
  std::vector<GLushort> _indices;
  std::vector<glm::vec3> _normals;
  std::vector<glm::vec2> _uv;

  GLuint _vertex_buffer;
  GLuint _color_buffer;
  GLuint _normal_buffer;
  GLuint _index_buffer;

public:
  Model(const std::string &file) noexcept;
  virtual ~Model();
  const GLfloat *getData() const;
  size_t getDataSize() const;
  const GLfloat *get_colors() const;
  size_t getColorsSize() const;
  const GLfloat *getNormals() const;
  size_t getNormalsSize() const;
  const std::vector<GLushort> &getIndices() const;
  void draw() const;
};

#endif
