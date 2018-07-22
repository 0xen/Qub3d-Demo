project(Viking)

set(source
	src/IRenderer.cpp
)

set(headers
	include/viking/API.hpp
	include/viking/IRenderer.hpp
)

include_directories(include)
add_library(Viking ${source} ${headers})

add_definitions(-DSUPPORTS_OPENGL11 -DSUPPORTS_OPENGL3)

find_package(Vulkan)
if(Vulkan_FOUND)
    message(STATUS "Found Vulkan")
endif()

