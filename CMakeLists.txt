cmake_minimum_required(VERSION 2.6)

set(project_name qub3d-demo)
project(${project_name})

# This just groups some CMake targets into a folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(code_root voxels-sandbox)
set(libs_root ${code_root}/third_party)

set(src_root ${code_root}/src)
set(src
    ${src_root}/main.cc
    ${src_root}/q3camera.cc
    ${src_root}/q3generator.cc
    ${src_root}/q3renderer.cc
    ${src_root}/q3window.cc
    ${src_root}/q3texture.cc
    ${src_root}/q3world.cc

    ${libs_root}/lodepng.cc
)

set(headers_root ${code_root}/include/qub3d)
set(headers
    ${headers_root}/q3camera.hpp
    ${headers_root}/q3opengl.hpp
    ${headers_root}/q3generator.hpp
    ${headers_root}/q3renderer.hpp
    ${headers_root}/q3window.hpp
    ${headers_root}/q3shared_constants.hpp
    ${headers_root}/q3texture.hpp
    ${headers_root}/q3world.hpp

    ${libs_root}/lodepng/lodepng.h
)

include_directories(${code_root}/include)
include_directories(${libs_root})

add_executable(${project_name} ${src} ${headers})

# Configure dependencies

set(libdeps ${CMAKE_CURRENT_LIST_DIR}/../qub3d-libdeps)

include_directories(${libdeps}/glm)
include_directories(${libdeps}/SDL2/include)

add_custom_command(TARGET ${project_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E
        copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
            "${CMAKE_CURRENT_BINARY_DIR}/assets/"
)

if(UNIX)
    target_link_libraries(${project_name} 
        ${libdeps}/SDL2/build/libSDL2-2.0.so
        GL
    )
elseif(WIN32)
    target_link_libraries(${project_name} 
        ${libdeps}/SDL2/build/Debug/SDL2d.lib
        opengl32.lib
    )

    add_custom_command(TARGET ${project_name} POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        "${libdeps}/SDL2/build/Debug/SDL2d.dll" 
                        $<TARGET_FILE_DIR:${project_name}>
    )
endif()

