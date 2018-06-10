set(SDL2_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/../../external/SDL2-2.0.8/include")

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(SDL2_PLATFORM "x64")
else (CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(SDL2_PLATFORM "x86")
endif (CMAKE_SIZEOF_VOID_P EQUAL 8)

set(SDL2_LIBRARIES
    "${CMAKE_CURRENT_LIST_DIR}/../../external/SDL2-2.0.8/lib/${SDL2_PLATFORM}/SDL2.lib"
    "${CMAKE_CURRENT_LIST_DIR}/../../external/SDL2-2.0.8/lib/${SDL2_PLATFORM}/SDL2main.lib"
    "${CMAKE_CURRENT_LIST_DIR}/../../external/SDL2-2.0.8/lib/${SDL2_PLATFORM}/SDL2test.lib")

# Copy SDL2.dll to locations where it's needed for simple debugging/development
configure_file(
	"${CMAKE_CURRENT_LIST_DIR}/../../external/SDL2-2.0.8/lib/${SDL2_PLATFORM}/SDL2.dll"
	"${CMAKE_CURRENT_BINARY_DIR}/omni-app/SDL2.dll"
	COPYONLY)

configure_file(
	"${CMAKE_CURRENT_LIST_DIR}/../../external/SDL2-2.0.8/lib/${SDL2_PLATFORM}/SDL2.dll"
	"${CMAKE_CURRENT_BINARY_DIR}/omni-tests/Debug/SDL2.dll"
	COPYONLY)

configure_file(
	"${CMAKE_CURRENT_LIST_DIR}/../../external/SDL2-2.0.8/lib/${SDL2_PLATFORM}/SDL2.dll"
	"${CMAKE_CURRENT_BINARY_DIR}/omni-tests/Release/SDL2.dll"
	COPYONLY)

