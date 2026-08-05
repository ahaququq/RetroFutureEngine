#include "Transform_Ry.hpp"

Transform_Ry::Transform_Ry(const float yaw): yaw(yaw) {}

glm::mat4 Transform_Ry::rotation() const {
	return yaw_matrix();
}

bool Transform_Ry::has_rotation() const {
	return yaw != 0;
}

bool Transform_Ry::can_rotate() const {
	return true;
}

glm::mat4 Transform_Ry::yaw_matrix() const {
	return glm::rotate(glm::identity<glm::mat4>(), glm::radians(-yaw), glm::vec3(0, 0, 1));
}

void Transform_Ry::rot_yaw(const float add_yaw) {
	yaw = std::fmodf(yaw + add_yaw + 180.0f, 360.0f) - 180.0;
}
