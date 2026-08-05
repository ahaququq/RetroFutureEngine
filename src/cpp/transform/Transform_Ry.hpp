#pragma once
#include "Transform.hpp"
#include "utils/glm.hpp"

class Transform_Ry:
	virtual public Transform
{ public:
	float yaw;

	// ReSharper disable once CppNonExplicitConvertingConstructor
	Transform_Ry(float yaw = 0);

	[[nodiscard]] glm::mat4 rotation() const override;
	[[nodiscard]] bool has_rotation() const override;
	[[nodiscard]] bool can_rotate() const override;

	[[nodiscard]] glm::mat4 yaw_matrix() const;

	/**
	 * Yaw function, keeps the internal yaw in [-180; 180]
	 * @param add_yaw How much to rotate
	 */
	void rot_yaw(float add_yaw);
};

using YawTransform = Transform_Ry;