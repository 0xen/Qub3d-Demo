#pragma once

// C++ Includes
#include <fstream>
#include <vector>
#include <string>
#include <vector>

// Windowing
#include <SDL.h>

// Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

// JSON I/O
#include <nlohmann/json.hpp>

// OpenGL
#include <SDL_opengl.h>

// Vulkan 
#include <vulkan/vulkan.h>


#include <qub3d/settings.hpp>

// Interface classes
#include <qub3d/IRenderer.hpp>
#include <qub3d/IWindow.hpp>

#include <qub3d/camera.hpp>

// OpenGL Side
#include <qub3d/GL11Window.hpp>
#include <qub3d/GL11Renderer.hpp>

// Vulkan Side
#include <qub3d/VulkanInitializers.hpp>
#include <qub3d/VulkanWindow.hpp>
#include <qub3d/VulkanInstance.hpp>
#include <qub3d/VulkanPhysicalDevice.hpp>
#include <qub3d/VulkanRenderer.hpp>