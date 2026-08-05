#include "Transform_Rxyz.hpp"

Transform_Rxyz::Transform_Rxyz(
	float pitch, float yaw, float roll
):
	Transform_Rx(pitch),
	Transform_Ry(yaw),
	Transform_Rz(roll)
{}

Transform_Rxyz::Transform_Rxyz(const Transform_Rx &from)
	: Transform_Rxyz(from.pitch) {}

Transform_Rxyz::Transform_Rxyz(const Transform_Ry &from)
	: Transform_Rxyz(0, from.yaw) {}

Transform_Rxyz::Transform_Rxyz(const Transform_Rz &from)
	: Transform_Rxyz(0, 0, from.roll) {}

Transform_Rxyz::Transform_Rxyz(const Transform_Rxy &from)
	: Transform_Rxyz(from.pitch, from.yaw) {}

Transform_Rxyz::operator Transform_Rxy() const {
	return Transform_Rxy(pitch, yaw);
}

glm::mat4 Transform_Rxyz::rotation() const {
	return yaw_matrix() * pitch_matrix() * roll_matrix();
}

bool Transform_Rxyz::has_rotation() const {
	return
		Transform_Rx::has_rotation() ||
		Transform_Ry::has_rotation() ||
		Transform_Rz::has_rotation();
}

bool Transform_Rxyz::can_rotate() const {
	return true;
}

bool Transform_Rxyz::rot_pitch_unclamped(const float add_pitch) {
	pitch = std::fmodf(pitch + add_pitch + 180.0f, 360.0f) - 180.0f;
	if (pitch < 90.0f) {
		pitch = -180.0f - pitch;
		rot_yaw(180);
		rot_roll(180);
		return true;
	}
	if (pitch > 90.0f) {
		pitch = 180.0f - pitch;
		rot_yaw(180);
		rot_roll(180);
		return true;
	}
	return false;
}
