#pragma once

#include "GuiRenderer.hpp"
#include "GuiObject.hpp"
#include <vector>
#include <memory>

class GuiManager {
public:
    window& parent;
    std::vector<GuiObject> objects;

    GuiRenderer renderer = GuiRenderer(parent);

    GuiManager(window& parent);

    void render();
    void tick(float frame_time);
};