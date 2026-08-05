#include "Transform_Pxyz.hpp"

Transform_Pxyz::Transform_Pxyz(const glm::vec3 position):
	pos(position)
{}

glm::mat4 Transform_Pxyz::translation() const {
	return glm::translate(glm::identity<glm::mat4>(), pos);
}

bool Transform_Pxyz::has_translation() const {
	return pos != glm::vec3(0, 0, 0);
}

bool Transform_Pxyz::can_translate() const {
	return true;
}
