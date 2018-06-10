set(omni_app "omni-app")

set(src_precompiled
	"src/precompiled/precompiled.h")

set(src_sample)

set(src_main
	"src/main.cpp")

set(all_sources
	${src_precompiled}
	${src_sample}
	${src_main})

add_executable(${omni_app} WIN32 ${all_sources})

source_group("src\\sample" FILES ${src_sample})
source_group("src\\precompiled" FILES ${src_precompiled})
source_group("src\\main" FILES ${src_main})

target_link_libraries(${omni_app} "omni-lib")

target_include_directories(${omni_app} PRIVATE "../")

set_target_properties(${omni_app} PROPERTIES CXX_STANDARD 17)
set_target_properties(${omni_app} PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)
set_target_properties(${omni_app} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
set_target_properties(${omni_app} PROPERTIES FOLDER "Project ${PROJECT_NAME}")
set_target_properties(${omni_app} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${src_precompiled})

cotire(${omni_app})