cmake_minimum_required(VERSION 2.6)

set(project_name qub3d-demo)
project(${project_name})

# This just groups some CMake targets into a folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# The root directory of any code in the demo (e.g contains src, include and third_party folders)
set(code_root demo_src)

# The root directory for any third party dependencies packaged with the demo
set(libs_root ${CMAKE_CURRENT_LIST_DIR}/demo_src/third_party)

# The root source directory that contains all of the demos source files
set(src_root ${code_root}/src)

set(src
    ${src_root}/main.cpp
    ${src_root}/window.cpp
    ${src_root}/settings.cpp
)

# The directory that contains all of the demos header files. Note this includes the `qub3d` prefix, and should not be used as part of
# a `include_directories` call as we want that `qub3d` prefix to keep everything cleaner.
# e.g.    #include <qub3d/window.hpp>
# and not #include <window.hpp>
set(headers_root ${code_root}/include/qub3d)

set(headers
    ${headers_root}/opengl.hpp
    ${headers_root}/window.hpp
    ${headers_root}/settings.hpp
    
    ${headers_root}/../nlohmann/json.hpp # JSON PARSING LIBRARY
)

add_executable(${project_name} ${src} ${headers})

include_directories(${code_root}/include)
include_directories(${libs_root}/glm)

# Now SDL2 is built automatically as part of the Qub3d Demo and does not need to be built seperatly
add_subdirectory(demo_src/third_party/SDL2)

# This places the SDL dependencies into nice folders in visual studio (keeps things tidy)
set_target_properties (SDL2 PROPERTIES FOLDER "Third Party/SDL2")
set_target_properties (SDL2main PROPERTIES FOLDER "Third Party/SDL2")
set_target_properties (SDL2-static PROPERTIES FOLDER "Third Party/SDL2")
set_target_properties (uninstall PROPERTIES FOLDER "Third Party/SDL2")

# This needs to come after the `add_subdirectory(.../SDL2)` because SDL sets up some include directories internally
include_directories(${libs_root}/SDL2/include)

# Link to the SDL2 librarys we need, note now we link to the static version of SDL
target_link_libraries(${project_name} SDL2-static)
target_link_libraries(${project_name} SDL2main)

# Link any platform specific libraries
if(WIN32) 
    target_link_libraries(${project_name} opengl32.lib)
endif()

if(UNIX)
    target_link_libraries(${project_name} GL)
endif()

add_custom_command(TARGET ${project_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
            "${CMAKE_CURRENT_BINARY_DIR}/assets/"
)

