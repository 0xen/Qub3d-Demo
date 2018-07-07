cmake_minimum_required(VERSION 2.6)

set(project_name qub3d-demo)
project(${project_name})

set(root voxels-sandbox)

set(src
    ${root}/src/main.cc
    ${root}/src/q3camera.cc
    ${root}/src/q3perlin.cc
    ${root}/src/q3renderer.cc
    ${root}/src/q3window.cc
)

set(headers
    ${root}/include/qub3d/q3camera.hpp
    ${root}/include/qub3d/q3opengl.hpp
    ${root}/include/qub3d/q3perlin.hpp
    ${root}/include/qub3d/q3renderer.hpp
    ${root}/include/qub3d/q3window.hpp
    ${root}/include/qub3d/shared_constants.hpp
)

include_directories(${root}/include)

set(libdeps ${CMAKE_CURRENT_LIST_DIR}/../qub3d-libdeps)

include_directories(${libdeps}/glm)
include_directories(${libdeps}/SDL2/include)

add_executable("${project_name}" ${src} ${headers})

if(UNIX)
    target_link_libraries(${project_name} 
        ${libdeps}/SDL2/build/libSDL2-2.0.so
        GL)
elseif(WIN32)
    target_link_libraries(${project_name} 
        ${libdeps}/SDL2/build/Debug/SDL2d.lib
        opengl32.lib)

    add_custom_command(TARGET ${project_name} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${libdeps}/SDL2/build/Debug/SDL2d.dll" 
        $<TARGET_FILE_DIR:${project_name}>)
endif()

