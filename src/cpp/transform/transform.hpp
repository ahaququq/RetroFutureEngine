#pragma once

#include "utils/glm.hpp"

class transform {
public:
	virtual glm::mat4 translation() const;
	virtual glm::mat4 rotation() const;
	virtual glm::mat4 scale() const;

	virtual bool has_translation() const;
	virtual bool has_rotation() const;
	virtual bool has_scale() const;

	virtual bool can_translate() const;
	virtual bool can_rotate() const;
	virtual bool can_scale() const;
	
	glm::mat4 matrix    (bool translate = true, bool rotate = true, bool scale = true) const;
	glm::mat4 inv_matrix(bool translate = true, bool rotate = true, bool scale = true) const;

	glm::vec3 apply    (glm::vec3 vec, bool translate = true, bool rotate = true, bool scale = true) const;
	glm::vec3 inv_apply(glm::vec3 vec, bool translate = true, bool rotate = true, bool scale = true) const;

	glm::vec3 translated    (glm::vec3 vec) const;
	glm::vec3 inv_translated(glm::vec3 vec) const;

	glm::vec3 rotated    (glm::vec3 vec) const;
	glm::vec3 inv_rotated(glm::vec3 vec) const;

	glm::vec3 scaled    (glm::vec3 vec) const;
	glm::vec3 inv_scaled(glm::vec3 vec) const;
};