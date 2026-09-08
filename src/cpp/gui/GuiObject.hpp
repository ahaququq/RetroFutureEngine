#pragma once

#include "GuiRenderer.hpp"

class GuiObject {
public:
    GuiObject() = delete;
    virtual ~GuiObject() = default;

    /// True if needs re-rendering
    bool changed = true;
    /// Render, will be skipped if changed is false
    virtual void render(GuiRenderer &renderer) = 0;
    /// Tick, called every frame, use for interaction and 
    /// set `changed` if re-rendering is needed
    virtual void tick(float frameTime) = 0;
};