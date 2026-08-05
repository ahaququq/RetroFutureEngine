#pragma once
#include "Transform.hpp"
#include "utils/glm.hpp"

class Transform_Pxyz:
	virtual public Transform
{ public:
	glm::vec3 pos;

	// ReSharper disable once CppNonExplicitConvertingConstructor
	Transform_Pxyz(glm::vec3 position = {0, 0, 0});

	[[nodiscard]] glm::mat4 translation() const override;
	[[nodiscard]] bool has_translation() const override;
	[[nodiscard]] bool can_translate() const override;
};

using PosTransform = Transform_Pxyz;