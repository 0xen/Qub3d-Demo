cmake_minimum_required(VERSION 2.6)

set(project_name qub3d-demo)
project(${project_name})

# This just groups some CMake targets into a folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(viking-renderer)

add_definitions(-DVIKING_SUPPORTS_GL11 -DVIKING_SUPPORTS_GL3)

find_package(Vulkan QUIET)

if(Vulkan_FOUND)
    add_definitions(-DVIKING_SUPPORTS_VULKAN)
else()
    message(WARNING "The Vulkan SDK cannot be found. Not compiling vulkan backend")
endif()
