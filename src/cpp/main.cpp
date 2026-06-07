#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "engine.hpp"
#include "utils/log.hpp"

GLFWwindow* main_window;

int main() {
	busy("Starting RetroFutureEngine...");
	const int ret = engine{}.main();
	if (ret) {
		fail("Exited RetroFutureEngine (With errors!)", "engine::main() returned " + std::to_string(ret));
	} else {
		ok("Exited RetroFutureEngine");
	}
	return ret;
}