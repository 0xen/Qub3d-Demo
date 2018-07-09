cmake_minimum_required(VERSION 2.6)

set(project_name qub3d-demo)
project(${project_name})

# This just groups some CMake targets into a folder
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set the root folder for actual code.
set(demo-root demo-src)
# Set root for the libraries required.
set(demo-libs ${demo-root}/third_party)

# Set demo-src folder, for easier adding src files.
set(demo-src ${demo-root}/src)
# Set src files
set(src
    ${demo-src}/main.cpp
)

# Set directory for demo-headers, to aid easier adding of headers.
set(demo-headers ${demo-root}/include/)
# Set headers
set(headers

)

add_executable(${project_name} ${src} ${headers})
