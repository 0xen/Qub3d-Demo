set(project_name Qub3d-Demo)
project(${project_name})

set(src
    src/main.cpp
)

set(headers
)

include_directories(include)
include_directories(../third_party/glm)
include_directories(../viking-renderer/include)

add_executable(Qub3d-Demo ${src} ${headers})

target_link_libraries(Qub3d-Demo Viking)
target_link_libraries(Qub3d-Demo SDL2main)


find_package(Vulkan)

if(Vulkan_FOUND)
	target_include_directories(${project_name} PRIVATE Vulkan::Vulkan)
	target_link_libraries(${project_name} Vulkan::Vulkan)
endif()