#pragma once
#include "Transform.hpp"
#include "utils/glm.hpp"

class Transform_Rx:
	virtual public Transform
{ public:
	float pitch;

	// ReSharper disable once CppNonExplicitConvertingConstructor
	Transform_Rx(float pitch = 0);

	[[nodiscard]] glm::mat4 rotation() const override;
	[[nodiscard]] bool has_rotation() const override;
	[[nodiscard]] bool can_rotate() const override;

	[[nodiscard]] glm::mat4 pitch_matrix() const;

	/**
	 * Clamped pitch function - keeps pitch in [-90; 90],
	 * discards any rotation beyond range
	 * @param add_pitch How much to rotate
	 * @return Whether clamping happened - if the rotation
	 *	requested couldn't be fully executed.
	 */
	bool rot_pitch_clamped(float add_pitch);
};

using PitchTransform = Transform_Rx;