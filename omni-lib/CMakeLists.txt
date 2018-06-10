set(omni_lib "omni-lib")

set(src_precompiled
	"src/precompiled/precompiled.h")

set(src_utilities
	"src/utilities/uncopyable.h")

set(src_engine
	"src/engine/buffer.h"
	"src/engine/engine.cpp"
	"src/engine/engine.h"
	"src/engine/render_commands.h"
	"src/engine/shader.h"
	"src/engine/shader_program.h"
	"src/engine/window.cpp"
	"src/engine/window.h")

set(src_interface
	"src/omni.h")

set(src_third_party
	${gfx_sources})

set(all_files
	${src_precompiled}
	${src_interface}
	${src_engine}
	${src_utilities}
	${src_third_party})

add_library(${omni_lib} ${all_files})

source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\interface" FILES ${src_interface})
source_group("src\\engine" FILES ${src_engine})
source_group("src\\third_party" FILES ${src_third_party})
source_group("src\\utilities" FILES ${src_utilities})

set_target_properties(${omni_lib} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${omni_lib} PROPERTIES CXX_STANDARD 17)
set_target_properties(${omni_lib} PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)
set_target_properties(${omni_lib} PROPERTIES FOLDER "Project ${PROJECT_NAME}")
set_target_properties(${omni_lib} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

target_link_libraries(${omni_lib} ${gfx_libraries})
target_include_directories(${omni_lib} PUBLIC ${gfx_includes})
target_include_directories(${omni_lib} PUBLIC ${imgui_includes})

cotire(${omni_lib})