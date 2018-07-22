cmake_minimum_required(VERSION 2.6)

set(project_name qub3d-demo)
project(${project_name})

# This just groups some CMake targets into a folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Now SDL2 is built automatically as part of the Qub3d Demo and does not need to be built seperatly
add_subdirectory(third_party/SDL2)

# This places the SDL dependencies into nice folders in visual studio (keeps things tidy)
set_target_properties (SDL2 PROPERTIES FOLDER "Third Party/SDL2")
set_target_properties (SDL2main PROPERTIES FOLDER "Third Party/SDL2")
set_target_properties (SDL2-static PROPERTIES FOLDER "Third Party/SDL2")
set_target_properties (uninstall PROPERTIES FOLDER "Third Party/SDL2")

# This needs to come after the `add_subdirectory(.../SDL2)` because SDL sets up some include directories internally
include_directories(third_party/SDL2/include)

add_subdirectory(viking-renderer)
add_subdirectory(qub3d-demo)
