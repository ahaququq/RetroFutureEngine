#include "window.hpp"

#include <stdexcept>

#include "utils/log.hpp"

window::window(glfw_context& context, const int width, const int height, const std::string &title): ctx(context) {
    busy("glfwCreateWindow()...");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!handle) {
        fail("glfwCreateWindow(); => 0");
        throw std::runtime_error("glfwCreateWindow() returned 0");
    }
    ok("glfwCreateWindow();  ");

    makeContextCurrent();

    busy("gladLoadGL()...");
    const int version = gladLoadGL(glfwGetProcAddress);
    if (!version) {
        fail("gladLoadGL(); => 0");
        throw std::runtime_error("gladLoadGL() returned 0");
    }
    ok(std::string{"gladLoadGL(); // Version: "} + std::to_string(version));
	const auto ver_str = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    ok(std::string{"glGetString(GL_VERSION); => "} + std::string{ver_str});
}

window::~window() {
    busy("glfwDestroyWindow()...");
    glfwDestroyWindow(handle);
    ok("glfwDestroyWindow();  ");
}

bool window::shouldClose() const {
    return glfwWindowShouldClose(handle);
}

void window::shouldClose(const bool close) const {
    glfwSetWindowShouldClose(handle, close);
}

void window::swapBuffers() const {
    glfwSwapBuffers(handle);
}

void window::viewport() const {
    const glm::ivec2 size = getFramebufferSize();
    makeContextCurrent();
    glViewport(0, 0, size.x, size.y);
}

glm::ivec2 window::getFramebufferSize() const {
    int width, height;
    glfwGetFramebufferSize(handle, &width, &height);
    return {width, height};
}

int window::getKey(const int key) const {
    return glfwGetKey(handle, key);
}

void window::makeContextCurrent() const {
    glfwMakeContextCurrent(handle);
}

void window::swapInterval(const int interval) const {
    makeContextCurrent();
    glfwSwapInterval(interval);
}
