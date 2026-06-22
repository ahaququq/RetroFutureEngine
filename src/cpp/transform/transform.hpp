#pragma once

#include "utils/glm.hpp"

class transform {
public:
	virtual ~transform() = default;

	[[nodiscard]] virtual glm::mat4 translation() const;
	[[nodiscard]] virtual glm::mat4 rotation() const;
	[[nodiscard]] virtual glm::mat4 scale() const;

	[[nodiscard]] virtual bool has_translation() const;
	[[nodiscard]] virtual bool has_rotation() const;
	[[nodiscard]] virtual bool has_scale() const;

	[[nodiscard]] virtual bool can_translate() const;
	[[nodiscard]] virtual bool can_rotate() const;
	[[nodiscard]] virtual bool can_scale() const;
	
	[[nodiscard]] glm::mat4 matrix    (bool do_translate = true, bool do_rotate = true, bool do_scale = true) const;
	[[nodiscard]] glm::mat4 inv_matrix(bool do_translate = true, bool do_rotate = true, bool do_scale = true) const;

	[[nodiscard]] glm::vec3 apply    (glm::vec3 vec, bool do_translate = true, bool do_rotate = true, bool do_scale = true) const;
	[[nodiscard]] glm::vec3 inv_apply(glm::vec3 vec, bool do_translate = true, bool do_rotate = true, bool do_scale = true) const;

	[[nodiscard]] glm::vec3 translated    (glm::vec3 vec) const;
	[[nodiscard]] glm::vec3 inv_translated(glm::vec3 vec) const;

	[[nodiscard]] glm::vec3 rotated    (glm::vec3 vec) const;
	[[nodiscard]] glm::vec3 inv_rotated(glm::vec3 vec) const;

	[[nodiscard]] glm::vec3 scaled    (glm::vec3 vec) const;
	[[nodiscard]] glm::vec3 inv_scaled(glm::vec3 vec) const;

	[[nodiscard]] glm::vec3 get_position() const;
	[[nodiscard]] glm::vec3 get_scale() const;

	[[nodiscard]] glm::vec3 forward(bool do_scale = false) const;
	[[nodiscard]] glm::vec3 right  (bool do_scale = false) const;
	[[nodiscard]] glm::vec3 up     (bool do_scale = false) const;

	[[nodiscard]] glm::vec3 forward_end(bool do_scale = false) const;
	[[nodiscard]] glm::vec3 right_end  (bool do_scale = false) const;
	[[nodiscard]] glm::vec3 up_end     (bool do_scale = false) const;
};