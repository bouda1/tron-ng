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
// Include standard headers
#include <iostream>

#include <cmath>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow *window;

// Include GLM
#define GLM_FORCE_CXX17
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "engine.hpp"
#include "motorcycle.hpp"
#include "zone.hpp"

using namespace glm;

GLuint load_shaders(const std::string &vertex_shader,
                    const std::string &fragment_shader) {
  GLuint vertexShaderObject, fragmentShaderObject;

  vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
  fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

  auto load_file = [](const std::string &filename, GLint *size) {
    std::ifstream f(filename);
    f.seekg(0, std::ios::end);
    *size = f.tellg();
    GLcharARB *buffer =
        static_cast<GLcharARB *>(malloc((*size + 1) * sizeof(GLcharARB)));
    f.seekg(0);
    f.read(buffer, *size);
    buffer[*size] = 0;
    return buffer;
  };
  GLint size;
  GLcharARB *buffer = load_file(vertex_shader, &size);
  glShaderSourceARB(vertexShaderObject, 1,
                    const_cast<const GLcharARB **>(&buffer), &size);
  std::cout << "Shader:\n" << buffer << std::endl;
  free(buffer);
  buffer = load_file(fragment_shader, &size);
  glShaderSourceARB(fragmentShaderObject, 1,
                    const_cast<const GLcharARB **>(&buffer), &size);
  std::cout << "Shader:\n" << buffer << std::endl;
  free(buffer);

  glCompileShaderARB(vertexShaderObject);
  glCompileShaderARB(fragmentShaderObject);
  GLint compiled;

  glGetObjectParameterivARB(vertexShaderObject, GL_COMPILE_STATUS, &compiled);
  assert(compiled);
  glGetObjectParameterivARB(fragmentShaderObject, GL_COMPILE_STATUS, &compiled);
  assert(compiled);

  GLint program = glCreateProgram();

  glAttachShader(program, vertexShaderObject);
  glAttachShader(program, fragmentShaderObject);

  glLinkProgram(program);

  GLint isLinked = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
  if (isLinked == GL_FALSE) {
    GLint maxLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> infoLog(maxLength);
    glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
    glDeleteProgram(program);
    std::cout << &infoLog[0] << std::endl;
    exit(2);
  }

  glDeleteShader(vertexShaderObject);
  glDeleteShader(fragmentShaderObject);
  return program;
}

void APIENTRY glDebugOutput(unsigned int source, unsigned int type,
                            unsigned int id, unsigned int severity, int length,
                            const char *message, const void *userParam) {
  // void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id,
  //                            GLenum severity, GLsizei length,
  //                            const GLchar *message, void *userParam) {
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
    return;

  std::cout << "---------------" << std::endl;
  std::cout << "Debug message (" << id << "): " << message << std::endl;

  switch (source) {
  case GL_DEBUG_SOURCE_API:
    std::cout << "Source: API";
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    std::cout << "Source: Window System";
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    std::cout << "Source: Shader Compiler";
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    std::cout << "Source: Third Party";
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    std::cout << "Source: Application";
    break;
  case GL_DEBUG_SOURCE_OTHER:
    std::cout << "Source: Other";
    break;
  }
  std::cout << std::endl;

  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    std::cout << "Type: Error";
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    std::cout << "Type: Deprecated Behaviour";
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    std::cout << "Type: Undefined Behaviour";
    break;
  case GL_DEBUG_TYPE_PORTABILITY:
    std::cout << "Type: Portability";
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    std::cout << "Type: Performance";
    break;
  case GL_DEBUG_TYPE_MARKER:
    std::cout << "Type: Marker";
    break;
  case GL_DEBUG_TYPE_PUSH_GROUP:
    std::cout << "Type: Push Group";
    break;
  case GL_DEBUG_TYPE_POP_GROUP:
    std::cout << "Type: Pop Group";
    break;
  case GL_DEBUG_TYPE_OTHER:
    std::cout << "Type: Other";
    break;
  }
  std::cout << std::endl;

  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH:
    std::cout << "Severity: high";
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    std::cout << "Severity: medium";
    break;
  case GL_DEBUG_SEVERITY_LOW:
    std::cout << "Severity: low";
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
    std::cout << "Severity: notification";
    break;
  }
  std::cout << std::endl;
  std::cout << std::endl;
}

int main(void) {
  // Initialise GLFW
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    getchar();
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // FIXME DBR: To enable debugging.
  // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

  GLint flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  //
  // Open a window and create its OpenGL context
  const GLuint width = 1024, height = 768;
  window = glfwCreateWindow(width, height, "Tron-ng", NULL, NULL);
  if (window == NULL) {
    fprintf(stderr,
            "Failed to open GLFW window. If you have an Intel GPU, they are "
            "not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
    getchar();
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }

  if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR,
                          GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it is closer to the camera than the former one
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  // Create and compile our GLSL program from the shaders
  GLuint programID = load_shaders(
      "/home/david/Projets/tron-ng/src/SimpleVertexShader.vertexshader",
      "/home/david/Projets/tron-ng/src/SimpleFragmentShader.fragmentshader");

  // Get a handle for our "MVP" uniform
  // Only during the initialization
  GLuint matrixID = glGetUniformLocation(programID, "MVP");

  // Projection matrix: 45° field of view, 4:3 ratio, display range : 0.1 unit
  // <-> 100 units
  glm::mat4 Projection = glm::perspective(
      glm::radians(45.0f),
      static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

  // Camera matrix
  glm::mat4 View;

  // Model matrix : an identity matrix (model will be at the origin)
  glm::mat4 model = glm::mat4(1.0f);

  // Our ModelViewProjection : multiplication of our 3 matrices
  glm::mat4 MVP;

  float angle = 0.0f;

  Engine engine(10);
  engine.addMotorcycle(new Motorcycle());
  engine.setZone(
      new Zone("/home/david/Projets/tron-ng/objects/zones/zone2.obj"));

  /* Maint graphical loop */
  do {
    // Clear the screen. It's not mentioned before Tutorial 02, but it can cause
    // flickering, so it's there nonetheless.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(programID);

    angle += 0.02f;
    // Let's move the Camera
    View = glm::lookAt(glm::vec3(10 * cosf(angle), 0, 10 * sinf(angle)),
                       glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    for (auto &m : engine.getMotorcycles()) {
      // Our ModelViewProjection : multiplication of our 3 matrices
      MVP = Projection * View * m->getPhysics().getModel();

      // Send our transformation to the currently bound shader,
      // in the "MVP" uniform
      glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

      m->draw();
    }

    engine.getZone()->draw();

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
         glfwWindowShouldClose(window) == 0);

  // Cleanup VBO
  glDeleteProgram(programID);
  glDeleteVertexArrays(1, &VertexArrayID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}
