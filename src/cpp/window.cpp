#include "window.hpp"

#include "utils/log.hpp"

window::window(glfw_context& context, int width, int height, std::string title): ctx(context) {
    busy("glfwCreateWindow()...");

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!handle) {
        fail("glfwCreateWindow(); => 0");
        throw "";
    }
    ok("glfwCreateWindow();  ");

    makeContextCurrent();

    busy("gladLoadGL()...");
    int version = gladLoadGL(glfwGetProcAddress);
    if (!version) {
        fail("gladLoadGL(); => 0");
        throw "";
    }
    ok(std::string{"gladLoadGL(); // Version: "} + std::to_string(version));
    const char* ver_str = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    ok(std::string{"glGetString(GL_VERSION); => "} + std::string{ver_str});
}

window::~window() {
    busy("glfwDestroyWindow()...");
    glfwDestroyWindow(handle);
    ok("glfwDestroyWindow();  ");
}

bool window::shouldClose() {
    return glfwWindowShouldClose(handle);
}

void window::shouldClose(bool close) {
    glfwSetWindowShouldClose(handle, close);
}

void window::swapBuffers() {
    glfwSwapBuffers(handle);
}

void window::viewport() {
    glm::ivec2 size = getFramebufferSize();
    makeContextCurrent();
    glViewport(0, 0, size.x, size.y);
}

glm::ivec2 window::getFramebufferSize() {
    int width, height;
    glfwGetFramebufferSize(handle, &width, &height);
    return {width, height};
}

int window::getKey(int key) {
    return glfwGetKey(handle, key);
}

void window::makeContextCurrent() {
    glfwMakeContextCurrent(handle);
}

void window::swapInterval(int interval) {
    makeContextCurrent();
    glfwSwapInterval(interval);
}