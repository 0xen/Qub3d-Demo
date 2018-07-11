cmake_minimum_required(VERSION 2.6)

set(project_name qub3d-demo)
project(${project_name})

# This just groups some CMake targets into a folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set the root folder for actual code.
set(code_root demo_src)
# Set root for the libraries required. This needs to done in this method, as they are for linking.
set(libs_root ${CMAKE_CURRENT_LIST_DIR}/demo_src/third_party)

# Set demo-src folder, for easier adding src files.
set(src_root ${code_root}/src)
# Set src files
set(src
    ${src_root}/main.cpp
)

# Set directory for demo-headers, to aid easier adding of headers.
set(headers_root ${code_root}/include/)
# Set headers
set(headers

)

add_executable(${project_name} ${src} ${headers})

include_directories(${libs_root}/glm)
include_directories(${libs_root}/SDL2/include)

if(UNIX)
    target_link_libraries(${project_name}
        ${libs_root}/SDL2/build/libSDL2-2.0.so
        GL
    )
endif()


