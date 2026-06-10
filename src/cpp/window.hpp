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
    
    window(glfw_context& context, int width = 640, int height = 480, std::string title = "Window");
    window(const window &) = delete;
    ~window();

    bool shouldClose();
    void shouldClose(bool close);
    void swapBuffers();
    void viewport();

    glm::ivec2 getFramebufferSize();
    int getKey(int key);

    void makeContextCurrent();
    void swapInterval(int interval);
};