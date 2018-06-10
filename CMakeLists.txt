cmake_minimum_required(VERSION 3.1)
project("omni" LANGUAGES C CXX VERSION 0.1.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "Predefined Targets")

include("scripts/cmake/googletest.cmake")
include("scripts/cmake/cotire.cmake")
include("scripts/cmake/opengl.cmake")
include("scripts/cmake/imgui.cmake")

add_subdirectory("omni-lib")
add_subdirectory("omni-app")
add_subdirectory("omni-tests")