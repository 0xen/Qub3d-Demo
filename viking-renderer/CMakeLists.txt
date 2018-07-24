set(project_name Viking)
project(${project_name})

set(common_source
	src/IRenderer.cpp
    src/IWindow.cpp
    src/SDLWindow.cpp
)

set(common_headers
	include/viking/API.hpp
	include/viking/IRenderer.hpp
    include/viking/WindowDescriptor.hpp
    include/viking/IWindow.hpp
    include/viking/SDLWindow.hpp
)

include_directories(include)

add_definitions(-DVIKING_SUPPORTS_OPENGL11 -DVIKING_SUPPORTS_OPENGL3)

set(source
    ${common_source}
)

set(headers
    ${common_headers}
)

find_package(Vulkan)

if(Vulkan_FOUND)
    add_definitions(-DVIKING_SUPPORTS_VULKAN)

    if(WIN32)
        add_definitions(-DVK_USE_PLATFORM_WIN32_KHR)
    else()
        message(FATAL "Vulkan is not currently supported on non windows platforms... Sorry :(")
    endif()

    set(vulkan_source
       src/vulkan/VulkanInitializers.cpp
       src/vulkan/VulkanInstance.cpp
       src/vulkan/VulkanPhysicalDevice.cpp
       src/vulkan/VulkanDevice.cpp
       src/vulkan/VulkanRenderer.cpp
       src/vulkan/VulkanWindow.cpp
       src/vulkan/VulkanSDLWindow.cpp
       src/vulkan/IVulkanSurface.cpp
       src/vulkan/VulkanSDLSurface.cpp
    )

    set(vulkan_headers
        include/viking/vulkan/VulkanInitializers.hpp
        include/viking/vulkan/VulkanInstance.hpp
        include/viking/vulkan/VulkanPhysicalDevice.hpp
        include/viking/vulkan/VulkanDevice.hpp
        include/viking/vulkan/VulkanRenderer.hpp
        include/viking/vulkan/VulkanWindow.hpp
        include/viking/vulkan/VulkanSDLWindow.hpp
        include/viking/vulkan/IVulkanSurface.hpp
        include/viking/vulkan/VulkanSDLSurface.hpp
    )

    include_directories(${Vulkan_INCLUDE_DIRS})

    list(APPEND source ${vulkan_source})
    list(APPEND headers ${vulkan_headers})

    source_group("Source Files\\Vulkan Backend" FILES ${vulkan_source})
    source_group("Header Files\\Vulkan Backend" FILES ${vulkan_headers})
endif()

add_library(Viking STATIC ${source} ${headers})

target_link_libraries(Viking SDL2-static)