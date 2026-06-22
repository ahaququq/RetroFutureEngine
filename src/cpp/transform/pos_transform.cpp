#include "pos_transform.hpp"

pos_transform::pos_transform(const glm::vec3 position):
	pos(position)
{}

glm::mat4 pos_transform::translation() const {
	return glm::translate(glm::identity<glm::mat4>(), pos);
}

bool pos_transform::has_translation() const {
	return pos != glm::vec3(0, 0, 0);
}

bool pos_transform::can_translate() const {
	return true;
}
