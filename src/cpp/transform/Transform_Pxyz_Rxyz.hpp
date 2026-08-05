#pragma once
#include "Transform_Rx.hpp"
#include "Transform_Rxyz.hpp"
#include "Transform_Rxy.hpp"
#include "Transform_Pxyz.hpp"
#include "Transform_Rz.hpp"
#include "Transform_Ry.hpp"

class Transform_Pxyz_Rxyz:
	virtual public Transform_Pxyz,
	virtual public Transform_Rxyz
{ public:
	Transform_Pxyz_Rxyz(glm::vec3 pos = {0, 0, 0}, float pitch = 0, float yaw = 0, float roll = 0);
	explicit Transform_Pxyz_Rxyz(const Transform_Rx &from);
	explicit Transform_Pxyz_Rxyz(const Transform_Ry &from);
	explicit Transform_Pxyz_Rxyz(const Transform_Rz &from);
	explicit Transform_Pxyz_Rxyz(const Transform_Rxy &from);
	explicit Transform_Pxyz_Rxyz(const Transform_Pxyz &from);
};

using Pos_PitchYawRoll_Transform = Transform_Pxyz_Rxyz;