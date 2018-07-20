#include <qub3d/graphics/IRenderer.hpp>
#include <qub3d/graphics/gl11/GL11Renderer.hpp>

#ifdef QUB3D_HAS_VULKAN_SDK 
    #include <qub3d/graphics/vulkan/VulkanRenderer.hpp>
#endif

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
#ifdef QUB3D_HAS_VULKAN_SDK
        return new VulkanRenderer(window);
#else
        // TODO: Fallthrough for no Vulkan renderer support. Cheat and use GL11 for now.
        return new GL11Renderer();
#endif
        break;
    }
    return nullptr;
}

IRenderer::IRenderer()
{
}