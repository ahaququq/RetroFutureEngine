#include "Transform_Rz.hpp"

Transform_Rz::Transform_Rz(const float roll): roll(roll) {}

glm::mat4 Transform_Rz::rotation() const {
	return roll_matrix();
}

bool Transform_Rz::has_rotation() const {
	return roll != 0;
}

bool Transform_Rz::can_rotate() const {
	return true;
}

glm::mat4 Transform_Rz::roll_matrix() const {
	return glm::rotate(glm::identity<glm::mat4>(), glm::radians(-roll), glm::vec3(0, 1, 0));
}

void Transform_Rz::rot_roll(const float add_roll) {
	roll = std::fmodf(roll + add_roll + 180.0f, 360.0f) - 180.0;
}
