set(omni_tests "omni-tests")

set(src_precompiled
	"src/precompiled/precompiled.h")

set(src_util
	"src/util/barrier.cpp")

set(src_engine
	"src/engine/application.cpp"
	"src/engine/render_engine.cpp"
	"src/engine/updater.cpp"
	"src/engine/window.cpp")

set(all_files
    ${src_precompiled}
	${src_engine}
	${src_util})

add_executable(${omni_tests} ${all_files})

source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\engine" FILES ${src_engine})
source_group("src\\util" FILES ${src_util})

target_include_directories(${omni_tests} PRIVATE "../")

target_link_libraries(${omni_tests} "gtest_main")
target_link_libraries(${omni_tests} "omni-lib")

set_target_properties(${omni_tests} PROPERTIES CXX_STANDARD 17)
set_target_properties(${omni_tests} PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)
set_target_properties(${omni_tests} PROPERTIES FOLDER "Project ${PROJECT_NAME}")
set_target_properties(${omni_tests} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

cotire(${omni_tests})