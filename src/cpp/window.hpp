#pragma once

#include "utils/gl.hpp"

#include <glm/common.hpp>
#include <glm/vec2.hpp>

#include <string>

#include "glfw_context.hpp"

class window {
private:
    GLFWwindow* handle;
public:
    glfw_context& ctx;
    
    window(glfw_context& context, int width = 640, int height = 480, const std::string &title = "Window");
    window(const window &) = delete;
    ~window();

    [[nodiscard]] bool shouldClose() const;
    void shouldClose(bool close) const;
    void swapBuffers() const;
    void viewport() const;

    [[nodiscard]] glm::ivec2 getFramebufferSize() const;
    [[nodiscard]] int getKey(int key) const;

    void makeContextCurrent() const;
    void swapInterval(int interval) const;
};