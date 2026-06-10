#include "engine.hpp"

#include "utils/log.hpp"
#include "utils/gl.hpp"

#include <iostream>

engine::engine() {
	ok("Initialised RetroFutureEngine");
}

engine::~engine() {
	ok("Terminated RetroFutureEngine");
}

int engine::main() {
	ok("Started RetroFutureEngine");

	material.link();

	main_window.swapInterval(1);
	int frame = 0;
	while (!main_window.shouldClose()) {
		glClearColor(1.0f, 0.5f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		material.use();
		glBegin(GL_TRIANGLES);
		glVertex3f(-0.5f, -0.5f, 0.0f);
		glVertex3f( 0.5f, -0.5f, 0.0f);
		glVertex3f( 0.0f,  0.5f, 0.0f);
		glEnd();

		main_window.swapBuffers();
		progress();
		std::cout << "F: " << frame++ << std::flush;
		if (main_window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			main_window.shouldClose(true);
			// std::cout << std::endl;
			busy("[ESC] Pressed, closing...");
		}
		ctx.pollEvents();
	}
	done("Main loop ended.");
	return 0;
}
