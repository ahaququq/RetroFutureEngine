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

	GCALL(glEnable(GL_DEPTH_TEST));

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
	GCALL(glEnableVertexAttribArray(material.getAttribLocation("position")));
	GCALL(glVertexAttribPointer(material.getAttribLocation("position"), 3, GL_FLOAT, true, 0, nullptr));

	buff_color.data<glm::vec3>(GL_ARRAY_BUFFER, colors);
	GCALL(glEnableVertexAttribArray(material.getAttribLocation("color")));
	GCALL(glVertexAttribPointer(material.getAttribLocation("color"), 3, GL_FLOAT, true, 0, nullptr));

	info("Pos: #" + std::to_string(material.getAttribLocation("position")));
    info("Col: #" + std::to_string(material.getAttribLocation("color")));

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

	gui_mgr.addTriangle({0.25f, 0.25f}, {0.75f, 0.75f}, {0.75f, 0.25f});
	gui_mgr.addRect({-0.5, -0.5}, {0.25, 0.25}, {0.7, 0.8, 0.9, 1.0}, 0.5, 15.0);
	gui_mgr.buildData();
	// gui_mgr.debugInfo();

	while (!main_window.shouldClose()) {
		main_window.viewport();
		GCALL(glClearColor(1.0f, 0.5f, 0.25f, 1.0f));
		GCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		material.use();

		buff_vertex.bind(GL_ARRAY_BUFFER);
		GCALL(glEnableVertexAttribArray(material.getAttribLocation("position")));
		GCALL(glVertexAttribPointer(material.getAttribLocation("position"), 3, GL_FLOAT, true, 0, nullptr));

		buff_color.bind(GL_ARRAY_BUFFER);
		GCALL(glEnableVertexAttribArray(material.getAttribLocation("color")));
		GCALL(glVertexAttribPointer(material.getAttribLocation("color"), 3, GL_FLOAT, true, 0, nullptr));

		buff_index.bind(GL_ELEMENT_ARRAY_BUFFER);


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

		if (true) {

			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0, 5.0, 0.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(frame), glm::vec3(0, 0, 1)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(5.1f * frame), glm::vec3(0, 1, 0));
			cam_mat = cam0.world_to_camera();
			view_mat = cam0.camera_to_view(main_window.getFramebufferSize());
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));

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
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));

			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(1.0, 5.0, 2.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(frame), glm::vec3(0, 0, 1));
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));


			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0, 5.0, 5.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(1, 0, 0));
			mv_mat = view_mat * cam_mat * cam0.camera_to_world() * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));

			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), 
					cam0.transform.pos + cam0.rot_camera_to_world(glm::vec3(0, 5, 0))
				) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(1, 0, 0));
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));


			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(5.0, 0.0, 0.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));

			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0, -5.0, 0.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));

			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(-5.0, 0.0, 0.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));



			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(5.0, 5.0, 0.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));

			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(5.0, -5.0, 0.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));

			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(-5.0, 5.0, 0.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));

			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(-5.0, -5.0, 0.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));


			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0, 0.0, -5.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));

			model_mat = 
				glm::translate(glm::identity<glm::mat4>(), glm::vec3(0.0, 0.0, 5.0)) * 
				glm::rotate(glm::identity<glm::mat4>(), glm::radians<float>(10 * frame), glm::vec3(0, 1, 0));
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));



			auto train = Transform_Pxyz(glm::vec3(0, 1, 0));
			model_mat = train.matrix();
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));

			auto train2 = Transform_Pxyz(glm::vec3(0, 2, 0));
			auto train3 = Transform_Rxy(45.0, 15.0);
			model_mat = train3.matrix() * train2.matrix();
			mv_mat = view_mat * cam_mat * model_mat;
			GCALL(glUniformMatrix4fv(material.getUniformLocation("model_view_mat"), 1, false, glm::value_ptr(mv_mat)));
			GCALL(glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr));
		}
		// glBegin(GL_TRIANGLES);
		// glVertex3f(-0.5f, -0.5f, 0.0f);
		// glVertex3f( 0.5f, -0.5f, 0.0f);
		// glVertex3f( 0.5f,  0.5f, 0.0f);
		// glEnd();

		// gui_mgr.material.use();
		// gui_mgr.data_valid = false;
		// gui_mgr.pos_buffer.data<float>(GL_ARRAY_BUFFER, {
		// 	-0.5, -0.5, 0.5, 0.5,
		// 	-0.5,  0.5, 0.5, 0.5,
		// 	 0.5, -0.5, 0.5, 0.5
		// });
		// glEnableVertexAttribArray(
		// 	gui_mgr.material.getAttribLocation("position"));
		// glVertexAttribPointer(
		// 	gui_mgr.material.getAttribLocation("position"), 
		// 	3, GL_FLOAT, false, 0, nullptr);
		// glDrawArrays(GL_TRIANGLES, 0, 3);


		gui_mgr.render();

		// GCALL(glDrawArrays(GL_TRIANGLES, 0, 3));

		// auto error_code = glGetError();
		// if (error_code) {
			// warn("Error #" + std::to_string(error_code));
		// }

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
