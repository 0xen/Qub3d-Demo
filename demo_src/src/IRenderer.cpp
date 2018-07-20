#include <qub3d\IRenderer.hpp>
#include <qub3d\GL11Renderer.hpp>
#include <qub3d\VulkanRenderer.hpp>

IRenderer * IRenderer::loadRenderer(IWindow * window, RenderingAPI api)
{
    switch (api)
    {
    case GL11:
        return new GL11Renderer();
        break;
    case GL3:
        break;
    case Vulkan:
        return new VulkanRenderer(window);
        break;
    }
    return nullptr;
}

IRenderer::IRenderer()
{
}