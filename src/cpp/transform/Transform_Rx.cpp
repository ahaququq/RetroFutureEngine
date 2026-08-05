#include "Transform_Rx.hpp"

Transform_Rx::Transform_Rx(const float pitch): pitch(pitch) {}

glm::mat4 Transform_Rx::rotation() const {
	return pitch_matrix();
}

bool Transform_Rx::has_rotation() const {
	return pitch != 0;
}

bool Transform_Rx::can_rotate() const {
	return true;
}

glm::mat4 Transform_Rx::pitch_matrix() const {
	return glm::rotate(glm::identity<glm::mat4>(), glm::radians(-pitch), glm::vec3(1, 0, 0));
}

constexpr float pitch_limit = 89.0f;

bool Transform_Rx::rot_pitch_clamped(const float add_pitch) {
	const float new_pitch = pitch + add_pitch;

	if (new_pitch >= pitch_limit) {
		pitch = pitch_limit;
		return true;
	}
	if (new_pitch < -pitch_limit) {
		pitch = -pitch_limit;
		return true;
	}
	pitch = new_pitch;
	return false;
}
