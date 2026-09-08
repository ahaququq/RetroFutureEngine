#include "GuiManager.hpp"

GuiManager::GuiManager(window& parent):
    parent(parent) {}

void GuiManager::render() {
    for (auto& object : objects) {
        if (!object.changed) 
            object.render(renderer);
    }
}

void GuiManager::tick(float frame_time) {
    for (auto& object: objects) {
        object.tick(frame_time);
    }
}
