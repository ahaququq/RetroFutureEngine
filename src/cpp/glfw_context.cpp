#include "glfw_context.hpp"

#include <stdexcept>

#include "utils/gl.hpp"
#include "utils/log.hpp"

glfw_context::glfw_context() {
    busy("glfwInit()...");
    if (!glfwInit()) {
		fail("glfwInit(); => 0");
		throw std::runtime_error("glfwInit() returned 0");
	}
	ok("glfwInit();");
}

glfw_context::~glfw_context() {
    busy("glfwTerminate()...");
	glfwTerminate();
	ok("glfwTerminate();");
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void glfw_context::pollEvents() { // NOLINT(*-convert-member-functions-to-static)
	glfwPollEvents();
}
