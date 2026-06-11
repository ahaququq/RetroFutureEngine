#include "engine.hpp"

#include "utils/log.hpp"
#include "utils/gl.hpp"
#include "graphics/buffer.hpp"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vec_swizzle.hpp>
#include <glm/gtx/quaternion.hpp>

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

	buffer vertex = buffer(main_window);
	buffer index = buffer(main_window);

	vertex.data<float>(GL_ARRAY_BUFFER, {
		-0.5, -0.5, 0.0,
		 0.5, -0.5, 0.0,
		-0.5,  0.5, 0.0,
		 0.5,  0.5, 0.0
	});

	index.data<unsigned int>(GL_ELEMENT_ARRAY_BUFFER, {
		0, 1, 3,
		0, 2, 3
	});

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(material.getAttribLocation("position"), 3, GL_FLOAT, true, 0, nullptr);

	while (!main_window.shouldClose()) {
		main_window.viewport();
		glClearColor(1.0f, 0.5f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		material.use();
		glm::mat4 mv_mat = glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(frame), glm::vec3(0, 0, 1)) * glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(5.1f * frame), glm::vec3(0, 1, 0));
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));

		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		// glBegin(GL_TRIANGLES);
		// glVertex3f(-0.5f, -0.5f, 0.0f);
		// glVertex3f( 0.5f, -0.5f, 0.0f);
		// glVertex3f( 0.5f,  0.5f, 0.0f);
		// glEnd();

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
