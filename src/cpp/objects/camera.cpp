#include "camera.hpp"

camera::camera(float f, glm::vec3 p, glm::quat r): fov(f), pos(p), rot(r) {

}

glm::mat4 camera::world_to_camera() const {
	glm::mat4 translation = glm::translate(glm::identity<glm::mat4>(), -pos);

	return 
		camera_inverse_rotation() * translation;
}

glm::mat4 camera::camera_rotation() const {
	glm::mat4 rotation = glm::toMat4(rot);
	return 
		glm::mat4{
			 0,  1,  0,  0,
			 1,  0,  0,  0,
			 0,  0,  1,  0,
			 0,  0,  0,  1
		} * rotation * 
		glm::mat4{
			 0,  1,  0,  0,
			 1,  0,  0,  0,
			 0,  0,  1,  0,
			 0,  0,  0,  1
		};
}

glm::mat4 camera::camera_inverse_rotation() const {
	glm::mat4 rotation = glm::toMat4(glm::inverse(rot));
	return 
		glm::mat4{
			 0,  1,  0,  0,
			 1,  0,  0,  0,
			 0,  0,  1,  0,
			 0,  0,  0,  1
		} * rotation * 
		glm::mat4{
			 0,  1,  0,  0,
			 1,  0,  0,  0,
			 0,  0,  1,  0,
			 0,  0,  0,  1
		};
}

glm::mat4 camera::camera_to_world() const {
	glm::mat4 translation = glm::translate(glm::identity<glm::mat4>(), pos);
	glm::mat4 rotation = glm::toMat4(rot);

	return
		glm::inverse(world_to_camera());
}

glm::vec3 camera::rot_camera_to_world(glm::vec3 vec) const {
	return glm::xyz(camera_rotation() * glm::vec4(vec, 1));
}

glm::vec3 camera::rot_camera_to_world_z_only(glm::vec3 vec) const {
	return glm::xyz(glm::mat4(
		 0,  1,  0,  0,
		 1,  0,  0,  0,
		 0,  0,  1,  0,
		 0,  0,  0,  1
	) * glm::toMat4(glm::quat(
		glm::eulerAngles(rot) * glm::vec3(0, 0, 1)
	)) * glm::mat4(
		 0,  1,  0,  0,
		 1,  0,  0,  0,
		 0,  0,  1,  0,
		 0,  0,  0,  1
	) * glm::vec4(vec, 1));
}

glm::mat4 camera::camera_to_view(glm::ivec2 viewport) const {
	glm::mat4 per = glm::perspectiveFov<float>(
		glm::radians<float>(fov), 
		viewport.x, viewport.y, 0.1, 50.0
	);

	return per * glm::mat4{
		 1,  0,  0,  0,
		 0,  0, -1,  0,
		 0,  1,  0,  0,
		 0,  0,  0,  1
	};
}

void camera::rotate(glm::vec3 axies) {
	glm::vec3 eul = 
		glm::mod(
			glm::eulerAngles(rot) + glm::radians(glm::vec3(
				axies.y, // Clockwise around Y+
				axies.x, // Clockwise around X+
				axies.z  // Clockwise around Z+
			)) + glm::vec3(glm::pi<float>()) * glm::vec3(1, 1, 1),
			glm::vec3(glm::pi<float>()) * glm::vec3(2, 2, 2)
		) - glm::vec3(glm::pi<float>()) * glm::vec3(1, 1, 1);

	if (eul.y > glm::pi<float>() * 0.5) {
		eul.y = glm::pi<float>() - eul.y;
		eul.z += glm::pi<float>();
		eul.x += glm::pi<float>();
	}

	if (eul.y < glm::pi<float>() * 0.5) {
		eul.y = -glm::pi<float>() - eul.y;
		eul.z += glm::pi<float>();
		eul.x += glm::pi<float>();
	}

	eul = 
		glm::mod(
			eul + glm::vec3(glm::pi<float>()) * glm::vec3(1, 1, 1),
			glm::vec3(glm::pi<float>()) * glm::vec3(2, 2, 2)
		) - glm::vec3(glm::pi<float>()) * glm::vec3(1, 1, 1);

	rot = glm::rotate(
		glm::identity<glm::quat>(),
		eul
	);
}

glm::vec3 camera::up_vector(bool lock) const {
	glm::vec3 up = rot_camera_to_world(glm::vec3(0, 0, 1));
	if (lock) {
		if (up.z > 0) {
			return glm::vec3(0, 0, 1);
		} else if (up.z < 0) {
			return glm::vec3(0, 0, -1);
		} else {
			return glm::vec3(0, 0, 1); // Default
		}
	} else {
		return up;
	}
}

bool camera::upside_down() const {
	return up_vector(true).z < 0;
}