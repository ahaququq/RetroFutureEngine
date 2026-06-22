#include "engine.hpp"
#include "utils/log.hpp"

GLFWwindow* main_window;

int main() {
	busy("Starting RetroFutureEngine...");
	int ret;
	try {
		ret = engine{}.main();
	} catch (...) {
		fail("Exception thrown out of RetroFutureEngine!");
		return 1;
	}

	if (ret) {
		fail("Exited RetroFutureEngine (With errors!)", "engine::main() returned " + std::to_string(ret));
	} else {
		ok("Exited RetroFutureEngine");
	}
	return ret;
}