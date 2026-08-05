#pragma once
#include "Transform_Rx.hpp"
#include "Transform_Ry.hpp"
#include "utils/glm.hpp"

class Transform_Rxy:
	virtual public Transform_Rx,
	virtual public Transform_Ry
{ public:

	// ReSharper disable once CppNonExplicitConvertingConstructor
	explicit Transform_Rxy(float pitch = 0, float yaw = 0);
	explicit Transform_Rxy(const Transform_Rx &from);
	explicit Transform_Rxy(const Transform_Ry &from);

	explicit operator Transform_Rx() const;
	explicit operator Transform_Ry() const;

	[[nodiscard]] glm::mat4 rotation() const override;
	[[nodiscard]] bool has_rotation() const override;
	[[nodiscard]] bool can_rotate() const override;
};

using PitchYawTransform = Transform_Rxy;