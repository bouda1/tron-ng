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
#include "model.hpp"
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

/**
 * @brief Construct a new Model:: Model object
 *
 * @param file The name of an obj file to build the model.
 */
Model::Model(const std::string &file) noexcept
    : _vertices{}, _colors{}, _indices{}, _normals{}, _uv{} {
  std::random_device rd;
  std::mt19937 gen(rd());

  std::ifstream f;

  f.open(file);

  std::string line;
  while (std::getline(f, line)) {
    if (line[0] == '#')
      continue;
    else if (strncmp("v ", line.c_str(), 2) == 0) {
      char *l = &line[0] + 2;
      float x = std::strtof(l, &l);
      float y = strtof(l, &l);
      float z = strtof(l, &l);
      _vertices.emplace_back(x, y, z);
      _colors.emplace_back(std::generate_canonical<float, 7>(gen),
                           std::generate_canonical<float, 7>(gen),
                           std::generate_canonical<float, 7>(gen));
    } else if (strncmp("vt ", line.c_str(), 3) == 0) {
      char *l = &line[0] + 3;
      float x = strtof(l, &l);
      float y = strtof(l, &l);
      _uv.emplace_back(x, y);
    } else if (strncmp("vn ", line.c_str(), 3) == 0) {
      char *l = &line[0] + 3;
      float x = strtof(l, &l);
      float y = strtof(l, &l);
      float z = strtof(l, &l);
      _normals.emplace_back(x, y, z);
    } else if (strncmp("f ", line.c_str(), 2) == 0) {
      char *l = &line[0] + 2;
      for (int i = 0; i < 3; i++) {
        short a = std::strtol(l, &l, 10);
        l++; // We skip the '/'
        short b = std::strtol(l, &l, 10);
        l++;
        short c = std::strtol(l, &l, 10);
        _indices.push_back(a - 1);
      }
    } else
      std::cout << "WARNING: not implemented to read '" << line << "'\n";
  }
  f.close();
  glGenBuffers(1, &_vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, getDataSize(), &getData()[0], GL_STATIC_DRAW);

  glGenBuffers(1, &_color_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
  glBufferData(GL_ARRAY_BUFFER, getColorsSize(), &get_colors()[0],
               GL_STATIC_DRAW);

  glGenBuffers(1, &_normal_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, _normal_buffer);
  glBufferData(GL_ARRAY_BUFFER, getNormalsSize(), &getNormals()[0],
               GL_STATIC_DRAW);

  glGenBuffers(1, &_index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndices().size() * sizeof(GLushort),
               &getIndices()[0], GL_STATIC_DRAW);
}

/**
 * @brief Destroy the Model:: Model object
 *
 */
Model::~Model() {
  glDeleteBuffers(1, &_vertex_buffer);
  glDeleteBuffers(1, &_color_buffer);
  glDeleteBuffers(1, &_index_buffer);
}

/**
 * @brief Returns the buffer containing data as a \a GLfloat* pointer.
 *
 * @return const GLfloat*
 */
const GLfloat *Model::getData() const {
  static_assert(sizeof(glm::vec3) == sizeof(GLfloat) * 3,
                "glm::vec3 is not a structure containing only 3 GLfloat...");
  glm::vec3 const *v = &_vertices[0];
  return reinterpret_cast<const GLfloat *>(v);
}

/**
 * @brief Returns the data size in bytes.
 *
 * @return size_t
 */
size_t Model::getDataSize() const {
  return _vertices.size() * 3 * sizeof(float);
}

/**
 * @brief Returns the normals buffer as a \a GLfloat* pointer.
 *
 * @return const GLfloat*
 */
const GLfloat *Model::getNormals() const {
  static_assert(sizeof(glm::vec3) == sizeof(GLfloat) * 3,
                "glm::vec3 is not a structure containing only 3 GLfloat...");
  glm::vec3 const *v = &_normals[0];
  return reinterpret_cast<const GLfloat *>(v);
}

/**
 * @brief Returns the normals buffer size in bytes.
 *
 * @return size_t
 */
size_t Model::getNormalsSize() const {
  return _normals.size() * 3 * sizeof(float);
}

const GLfloat *Model::get_colors() const {
  static_assert(sizeof(glm::vec3) == sizeof(GLfloat) * 3,
                "glm::vec3 is not a structure containing only 3 GLfloat...");
  glm::vec3 const *v = &_colors[0];
  return reinterpret_cast<const GLfloat *>(v);
}

size_t Model::getColorsSize() const {
  return _colors.size() * 3 * sizeof(float);
}

const std::vector<GLushort> &Model::getIndices() const { return _indices; }

void Model::draw() const {
  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(0); // Vertices
  glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
  glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but
                           // must match the layout in the shader.
                        3, // size
                        GL_FLOAT, // type
                        false,    // normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
  );

  // 2nd attribute buffer : colors
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, _color_buffer);
  glVertexAttribPointer(1,        // attribute
                                  // must match the layout in the shader.
                        3,        // size
                        GL_FLOAT, // type
                        false,    // normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
  );

  // 2nd attribute buffer : normals
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, _normal_buffer);
  glVertexAttribPointer(2,        // attribute
                                  // must match the layout in the shader.
                        3,        // size
                        GL_FLOAT, // type
                        false,    // normalized?
                        0,        // stride
                        (void *)0 // array buffer offset
  );

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
  glDrawElements(GL_TRIANGLES,        // mode
                 getIndices().size(), // count
                 GL_UNSIGNED_SHORT,   // type
                 (void *)0);

  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
}
