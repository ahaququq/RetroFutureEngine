#pragma once
#include "Transform_Rx.hpp"
#include "Transform_Rxy.hpp"
#include "Transform_Rz.hpp"
#include "Transform_Ry.hpp"

class Transform_Rxyz:
	virtual public Transform_Rx,
	virtual public Transform_Ry,
	virtual public Transform_Rz
{ public:
	Transform_Rxyz(float pitch = 0, float yaw = 0, float roll = 0);
	explicit Transform_Rxyz(const Transform_Rx &from);
	explicit Transform_Rxyz(const Transform_Ry &from);
	explicit Transform_Rxyz(const Transform_Rz &from);
	explicit Transform_Rxyz(const Transform_Rxy &from);

	explicit operator Transform_Rxy() const;

	[[nodiscard]] glm::mat4 rotation() const override;
	[[nodiscard]] bool has_rotation() const override;
	[[nodiscard]] bool can_rotate() const override;

	/**
	 * Unclamped pitch function - allows to flip upside down
	 * @warning When turning upside down it's the callers responsibility
	 *	to correct the direction - if you are rolled upside down, remember to
	 *	change the controls accordingly - invert the pitch axis.
	 * @param add_pitch How much to rotate
	 * @return Whether we flipped upside down
	 */
	bool rot_pitch_unclamped(float add_pitch);
};

using PitchYawRoll_Transform = Transform_Rxyz;