#include "glfw_context.hpp"

#include "utils/gl.hpp"
#include "utils/log.hpp"

glfw_context::glfw_context() {
    busy("glfwInit()...");
    if (!glfwInit()) {
		fail("glfwInit(); => 0");
		throw "GlfwInitFailed";
	}
	ok("glfwInit();  ");
}

glfw_context::~glfw_context() {
    busy("glfwTerminate()...");
	glfwTerminate();
	ok("glfwTerminate();  ");
}

void glfw_context::pollEvents() {
	glfwPollEvents();
}