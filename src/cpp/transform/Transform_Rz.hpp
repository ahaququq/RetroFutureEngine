#pragma once
#include "Transform.hpp"
#include "utils/glm.hpp"

class Transform_Rz:
	virtual public Transform
{ public:
	float roll;

	// ReSharper disable once CppNonExplicitConvertingConstructor
	Transform_Rz(float roll = 0);

	[[nodiscard]] glm::mat4 rotation() const override;
	[[nodiscard]] bool has_rotation() const override;
	[[nodiscard]] bool can_rotate() const override;

	[[nodiscard]] glm::mat4 roll_matrix() const;

	/**
	 * Roll function, keeping internal roll in [-180; 180]
	 * @param add_roll How much to rotate
	 */
	void rot_roll(float add_roll);
};

using RollTransform = Transform_Rz;