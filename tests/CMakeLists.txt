include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.8.0
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif ()

add_executable(ut "")
include_directories(${PROJECT_SOURCE_DIR}/src)

target_sources(ut
    PRIVATE
      tree.cpp
)

target_link_libraries(ut
    PRIVATE
    gtest_main
)

add_test(
    NAME google_test
    COMMAND $<TARGET_FILE:ut>
)
