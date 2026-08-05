#include "Camera.hpp"

#include <utility>

Camera::Camera(
	const float f,
	Transform_Pxyz_Rxyz transform
):
	transform(std::move(transform)),
	fov(f)
{}

glm::mat4 Camera::world_to_camera() const {
	return transform.inv_matrix();
}

glm::mat4 Camera::camera_rotation() const {
	return transform.rotation();
}

glm::mat4 Camera::camera_inverse_rotation() const {
	return transform.inv_rotation();
}

glm::mat4 Camera::camera_to_world() const {
	return transform.matrix();
}

glm::vec3 Camera::rot_camera_to_world(const glm::vec3 vec) const {
	return transform.rotated(vec);
}

glm::vec3 Camera::rot_camera_to_world_z_only(const glm::vec3 vec) const {
	// ReSharper disable once CppRedundantCastExpression
	return static_cast<Transform_Ry>(transform).rotated(vec); // NOLINT(*-slicing)
	// YES, I KNOW I'M SLICING THE OBJECT, LET ME DO IT IN PEACE
}

glm::mat4 Camera::camera_to_view(glm::ivec2 viewport) const {
	const glm::mat4 per = glm::perspectiveFov<float>(
		glm::radians<float>(fov), 
		viewport.x, viewport.y, 0.1f, 50.0f
	);

	return per * glm::mat4{
		 1,  0,  0,  0,
		 0,  0, -1,  0,
		 0,  1,  0,  0,
		 0,  0,  0,  1
	};
}

glm::vec3 Camera::up_vector(const bool lock) const {
	const glm::vec3 up = rot_camera_to_world(glm::vec3(0, 0, 1));
	if (lock) {
		if (up.z > 0) {
			return {0, 0, 1};
		}
		if (up.z < 0) {
			return {0, 0, -1};
		}
		return {0, 0, 1}; // Default
	}
	return up;
}

bool Camera::upside_down() const {
	return up_vector(true).z < 0;
}