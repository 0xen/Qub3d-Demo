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
    ${src_root}/IWindow.cpp
    ${src_root}/settings.cpp
    ${src_root}/camera.cpp

    ${src_root}/graphics/IRenderer.cpp
    ${src_root}/graphics/gl11/GL11Window.cpp
    ${src_root}/graphics/gl11/GL11Renderer.cpp
)

# The directory that contains all of the demos header files. Note this includes the `qub3d` prefix, and should not be used as part of
# a `include_directories` call as we want that `qub3d` prefix to keep everything cleaner.
# e.g.    #include <qub3d/window.hpp>
# and not #include <window.hpp>
set(headers_root ${code_root}/include/qub3d)

set(headers
    ${headers_root}/IWindow.hpp
    ${headers_root}/settings.hpp
    ${headers_root}/camera.hpp
    ${headers_root}/graphics/IRenderer.hpp
    ${headers_root}/graphics/RenderingAPI.hpp

    ${headers_root}/graphics/gl11/GL11Window.hpp
    ${headers_root}/graphics/gl11/GL11Renderer.hpp

    ${headers_root}/../nlohmann/json.hpp # JSON PARSING LIBRARY
)

if (NOT CMAKE_VERSION VERSION_LESS 3.7.0)
    message(STATUS "Using module to find Vulkan")
    find_package(Vulkan QUIET)
endif()

if (NOT Vulkan_FOUND)
    message(WARNING "Vulkan SDK cannot be found. Using OpenGL renderer backend instead.")
else()
    add_definitions(-DQUB3D_HAS_VULKAN_SDK)
    list(APPEND src
        ${src_root}/graphics/vulkan/VulkanRenderer.cpp
        ${src_root}/graphics/vulkan/VulkanWindow.cpp
        ${src_root}/graphics/vulkan/VulkanInstance.cpp
        ${src_root}/graphics/vulkan/VulkanInitializers.cpp
        ${src_root}/graphics/vulkan/VulkanPhysicalDevice.cpp
    )

    list(APPEND headers
        ${headers_root}/graphics/vulkan/VulkanRenderer.hpp
        ${headers_root}/graphics/vulkan/VulkanWindow.hpp
        ${headers_root}/graphics/vulkan/VulkanInstance.hpp
        ${headers_root}/graphics/vulkan/VulkanInitializers.hpp
        ${headers_root}/graphics/vulkan/VulkanPhysicalDevice.hpp
    )
endif()

add_executable(${project_name} ${src} ${headers})

source_group("Source Files\\Renderer" FILES
    ${src_root}/GL11Renderer.cpp
    ${src_root}/VulkanRenderer.cpp
)

source_group("Header Files\\Renderer" FILES
    ${headers_root}/IRenderer.hpp
    ${headers_root}/GL11Renderer.hpp
    ${headers_root}/VulkanRenderer.hpp
)

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

add_custom_command(TARGET ${project_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
            "${CMAKE_CURRENT_BINARY_DIR}/assets/"
)

