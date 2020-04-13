
# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (tron-ng VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

OPTION(WITH_TESTING "Enable unit tests" ON)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.2 REQUIRED)
find_package(glm REQUIRED)
find_package(Boost 1.59.0 REQUIRED)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

add_executable(tron-ng
        src/data.cpp
        src/data.hpp
        src/engine.cpp
        src/engine.hpp
        src/main.cpp
        src/model.cpp
        src/model.hpp
        src/motorcycle.cpp
        src/motorcycle.hpp
        src/physics.cpp
        src/physics.hpp
        src/tree.cpp
        src/tree.hpp
        src/zone.cpp
        src/zone.hpp
        )

target_link_libraries(tron-ng ${OPENGL_LIBRARY} glfw GLEW pthread)

if (WITH_TESTING)
  enable_testing()
  add_subdirectory(tests)
endif ()
