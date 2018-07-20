#pragma once

#include <qub3d/graphics/IRenderer.hpp>

class GL11Renderer : public IRenderer
{
public:
    virtual void render();
private:
};
