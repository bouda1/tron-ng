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
#ifndef _MODEL_HPP_
#define _MODEL_HPP_
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

class Model {
protected:
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
