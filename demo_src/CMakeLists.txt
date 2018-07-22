project(Qub3dDemo)

set(source
    src/main.cpp
    src/settings.cpp
)

set(headers
    include/qub3d/settings.hpp

    include/nlohmann/json.hpp
)

include_directories(include)
include_directories(third_party/glm)


# Link to the SDL2 librarys we need, note now we link to the static version of SDL
target_link_libraries(${project_name} SDL2-static)
target_link_libraries(${project_name} SDL2main)

if (Vulkan_FOUND)
    target_link_libraries(${project_name} Vulkan::Vulkan)
endif()

# Link any platform specific libraries
if(WIN32) 
    target_link_libraries(${project_name} opengl32.lib)
endif()

if(UNIX)
    target_link_libraries(${project_name} GL)
endif()