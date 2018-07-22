project(Qub3d-Demo)

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