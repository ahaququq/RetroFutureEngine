#include "Transform_Rxy.hpp"

Transform_Rxy::Transform_Rxy(
	const float pitch, const float yaw
): Transform_Rx(pitch), Transform_Ry(yaw) {}

Transform_Rxy::Transform_Rxy(const Transform_Rx &from)
	: Transform_Rxy(from.pitch) {}

Transform_Rxy::Transform_Rxy(const Transform_Ry &from)
	: Transform_Rxy(0, from.yaw) {}

glm::mat4 Transform_Rxy::rotation() const {
	return yaw_matrix() * pitch_matrix();
}

bool Transform_Rxy::has_rotation() const {
	return
		Transform_Rx::has_rotation() ||
		Transform_Ry::has_rotation();
}

bool Transform_Rxy::can_rotate() const {
	return true;
}