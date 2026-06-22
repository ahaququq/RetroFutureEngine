#pragma once
#include "transform.hpp"
#include "utils/glm.hpp"

class pos_transform: public transform {
public:
	glm::vec3 pos;

	// ReSharper disable once CppNonExplicitConvertingConstructor
	pos_transform(glm::vec3 position);

	[[nodiscard]] glm::mat4 translation() const override;
	[[nodiscard]] bool has_translation() const override;
	[[nodiscard]] bool can_translate() const override;
};