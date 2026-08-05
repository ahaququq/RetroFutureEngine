#include "engine.hpp"

#include "utils/log.hpp"
#include "utils/gl.hpp"
#include "utils/glm.hpp"
#include "graphics/buffer.hpp"
#include "objects/Camera.hpp"

#include <iostream>

#include "transform/Transform_Rxy.hpp"
#include "transform/Transform_Pxyz.hpp"
#include "transform/Transform.hpp"

engine::engine() {
	ok("Initialised RetroFutureEngine");
}

engine::~engine() {
	ok("Terminated RetroFutureEngine");
}

int engine::main() {
	ok("Started RetroFutureEngine");

	glEnable(GL_DEPTH_TEST);

	material.link();

	main_window.swapInterval(1);
	int frame = 0;

	buffer buff_vertex = buffer(main_window);
	buffer buff_color = buffer(main_window);
	buffer buff_index = buffer(main_window);

	std::vector<glm::vec3> vertices = {
		{-0.5, -0.5, -0.0},
		{ 0.5, -0.5, -0.0},
		{-0.5,  0.5, -0.0},
		{ 0.5,  0.5, -0.0}
	};


	std::vector<glm::vec3> colors = {
		{0, 0, 0},
		{1, 0, 0},
		{0, 1, 0},
		{1, 1, 0}
	};

	buff_vertex.data<glm::vec3>(GL_ARRAY_BUFFER, vertices);
	glEnableVertexAttribArray(material.getAttribLocation("position"));
	glVertexAttribPointer(material.getAttribLocation("position"), 3, GL_FLOAT, true, 0, nullptr);

	buff_color.data<glm::vec3>(GL_ARRAY_BUFFER, colors);
	glEnableVertexAttribArray(material.getAttribLocation("color"));
	glVertexAttribPointer(material.getAttribLocation("color"), 3, GL_FLOAT, true, 0, nullptr);

	buff_index.data<unsigned int>(GL_ELEMENT_ARRAY_BUFFER, {
		0, 1, 3,
		0, 2, 3
	});


	Camera cam0 = Camera(120.0);

	glm::mat4 model_mat;
	glm::mat4 cam_mat;
	glm::mat4 view_mat;
	glm::mat4 mv_mat = model_mat * view_mat;

	cam0.transform.pitch = 0;
	cam0.transform.yaw   = 0;
	cam0.transform.roll  = 0;

	info("Cam  Matrix: " + glm::to_string(cam0.world_to_camera()));
	info("View Matrix: " + glm::to_string(cam0.camera_to_view(main_window.getFramebufferSize())));

	while (!main_window.shouldClose()) {
		main_window.viewport();
		glClearColor(1.0f, 0.5f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		material.use();

		const float speed = 0.2;

		if (main_window.getKey(GLFW_KEY_D) == GLFW_PRESS) {
			cam0.transform.pos += cam0.rot_camera_to_world_z_only(glm::vec3(speed * -(cam0.upside_down() * 2 - 1), 0, 0));
		}
		if (main_window.getKey(GLFW_KEY_A) == GLFW_PRESS) {
			cam0.transform.pos += cam0.rot_camera_to_world_z_only(glm::vec3(-speed * -(cam0.upside_down() * 2 - 1), 0, 0));
		}

		if (main_window.getKey(GLFW_KEY_W) == GLFW_PRESS) {
			cam0.transform.pos += cam0.rot_camera_to_world_z_only(glm::vec3(0, speed, 0));
		}
		if (main_window.getKey(GLFW_KEY_S) == GLFW_PRESS) {
			cam0.transform.pos += cam0.rot_camera_to_world_z_only(glm::vec3(0, -speed, 0));
		}

		if (main_window.getKey(GLFW_KEY_SPACE) == GLFW_PRESS) {
			cam0.transform.pos += glm::vec3(0, 0, speed * -(cam0.upside_down() * 2 - 1));
		}
		if (main_window.getKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			cam0.transform.pos += glm::vec3(0, 0, -speed * -(cam0.upside_down() * 2 - 1));
		}

		if (main_window.getKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
			cam0.transform.rot_yaw(-1.0 * -(cam0.upside_down() * 2 - 1));
		}
		if (main_window.getKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
			cam0.transform.rot_yaw(1.0 * -(cam0.upside_down() * 2 - 1));
		}
		
		if (main_window.getKey(GLFW_KEY_UP) == GLFW_PRESS) {
			cam0.transform.rot_pitch_clamped(-1.0 * -(cam0.upside_down() * 2 - 1));
		}
		if (main_window.getKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
			cam0.transform.rot_pitch_clamped(1.0 * -(cam0.upside_down() * 2 - 1));
		}
		
		if (main_window.getKey(GLFW_KEY_E) == GLFW_PRESS) {
			cam0.transform.rot_roll(-1.0);
		}
		if (main_window.getKey(GLFW_KEY_Q) == GLFW_PRESS) {
			cam0.transform.rot_roll(1.0);
		}

		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0, 5.0, 0.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(frame), glm::vec3(0, 0, 1)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(5.1f * frame), glm::vec3(0, 1, 0));
		cam_mat = cam0.world_to_camera();
		view_mat = cam0.camera_to_view(main_window.getFramebufferSize());
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		progress();
		std::cout << "F: " << frame++;
		// std::cout << " CR: " << glm::to_string(glm::degrees(glm::eulerAngles(cam0.rot)));
		std::cout << " Vert0: " << glm::to_string(vertices[0]);
		glm::vec4 after = model_mat * glm::vec4(vertices[0], 1.0);
		std::cout << " -> " << glm::to_string(glm::xyz(after) / after.w);
		after = cam_mat * after;
		std::cout << " -> " << glm::to_string(glm::xyz(after) / after.w);
		after = view_mat * after;
		std::cout << " -> " << glm::to_string(glm::xyz(after) / after.w);
		std::cout << std::flush;

		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(1.0, 5.0, 0.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(5.1f * frame), glm::vec3(0, 1, 0));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(1.0, 5.0, 2.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(frame), glm::vec3(0, 0, 1));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);


		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0, 5.0, 5.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(1, 0, 0));
		mv_mat = view_mat * cam_mat * cam0.camera_to_world() * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), 
				cam0.transform.pos + cam0.rot_camera_to_world(glm::vec3(0, 5, 0))
			) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(1, 0, 0));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);


		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(5.0, 0.0, 0.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0, -5.0, 0.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(-5.0, 0.0, 0.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);



		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(5.0, 5.0, 0.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(5.0, -5.0, 0.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(-5.0, 5.0, 0.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(-5.0, -5.0, 0.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);


		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0, 0.0, -5.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		model_mat = 
			glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0, 0.0, 5.0)) * 
			glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);



		auto train = Transform_Pxyz(glm::vec3(0, 1, 0));
		model_mat = train.matrix();
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		auto train2 = Transform_Pxyz(glm::vec3(0, 2, 0));
		auto train3 = Transform_Rxy(45.0, 15.0);
		model_mat = train3.matrix() * train2.matrix();
		mv_mat = view_mat * cam_mat * model_mat;
		glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat));
		glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);

		// glBegin(GL_TRIANGLES);
		// glVertex3f(-0.5f, -0.5f, 0.0f);
		// glVertex3f( 0.5f, -0.5f, 0.0f);
		// glVertex3f( 0.5f,  0.5f, 0.0f);
		// glEnd();

		main_window.swapBuffers();
		
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
