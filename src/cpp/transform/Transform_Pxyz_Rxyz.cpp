#include "Transform_Pxyz_Rxyz.hpp"

Transform_Pxyz_Rxyz::Transform_Pxyz_Rxyz(
	const glm::vec3 pos,
	const float pitch,
	const float yaw,
	const float roll
):
	Transform_Pxyz(pos),
	Transform_Rxyz(pitch, yaw, roll)
{}

Transform_Pxyz_Rxyz::Transform_Pxyz_Rxyz(const Transform_Rx &from)
	: Transform_Pxyz_Rxyz({0, 0, 0}, from.pitch) {}

Transform_Pxyz_Rxyz::Transform_Pxyz_Rxyz(const Transform_Ry &from)
	: Transform_Pxyz_Rxyz({0, 0, 0}, 0, from.yaw) {}

Transform_Pxyz_Rxyz::Transform_Pxyz_Rxyz(const Transform_Rz &from)
	: Transform_Pxyz_Rxyz({0, 0, 0}, 0, 0, from.roll) {}

Transform_Pxyz_Rxyz::Transform_Pxyz_Rxyz(const Transform_Rxy &from)
	: Transform_Pxyz_Rxyz({0, 0, 0}, from.pitch, from.yaw) {}

Transform_Pxyz_Rxyz::Transform_Pxyz_Rxyz(const Transform_Pxyz &from)
	: Transform_Pxyz_Rxyz(from.pos) {}