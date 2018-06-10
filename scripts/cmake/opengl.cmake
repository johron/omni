find_package(OpenGL REQUIRED)

add_subdirectory("third_party/glfw")

set(gfx_libraries 
    "opengl32"
    "glfw")

set(gfx_sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/src/glad.c")

set(gfx_includes
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glfw/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glfw/deps"
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm")