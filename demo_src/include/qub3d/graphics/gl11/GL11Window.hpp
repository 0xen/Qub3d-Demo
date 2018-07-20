#pragma once

#include <qub3d\IWindow.hpp>

class GL11Window : public IWindow
{
  public:
      GL11Window(const char *title, int w, int h);
};