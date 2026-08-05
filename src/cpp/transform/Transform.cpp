#include "Transform.hpp"

glm::mat4 Transform::translation() const {
    return glm::identity<glm::mat4>();
}

glm::mat4 Transform::rotation() const {
    return glm::identity<glm::mat4>();
}

glm::mat4 Transform::scale() const {
    return glm::identity<glm::mat4>();
}

glm::mat4 Transform::inv_translation() const {
	return glm::inverse(translation());
}

glm::mat4 Transform::inv_rotation() const {
	return glm::inverse(rotation());
}

glm::mat4 Transform::inv_scale() const {
	return glm::inverse(scale());
}


bool Transform::has_translation() const {
    return false;
}

bool Transform::has_rotation() const {
    return false;
}

bool Transform::has_scale() const {
    return false;
}



bool Transform::can_translate() const {
    return false;
}

bool Transform::can_rotate() const {
    return false;
}

bool Transform::can_scale() const {
    return false;
}


inline glm::mat4 Transform::matrix(const bool do_translate, const bool do_rotate, const bool do_scale) const {
    auto result = glm::identity<glm::mat4>();
	if (do_scale    ) result = scale      () * result;
	if (do_rotate   ) result = rotation   () * result;
	if (do_translate) result = translation() * result;
    return result;
}

inline glm::mat4 Transform::inv_matrix(const bool do_translate, const bool do_rotate, const bool do_scale) const {
	auto result = glm::identity<glm::mat4>();
	if (do_translate) result = inv_translation() * result;
	if (do_rotate   ) result = inv_rotation   () * result;
	if (do_scale    ) result = inv_scale      () * result;
	return result;
}

glm::vec3 Transform::apply(const glm::vec3 vec, const bool do_translate, const bool do_rotate, const bool do_scale) const {
    return glm::xyz(matrix(do_translate, do_rotate, do_scale) * glm::vec4(vec, 1));
}

glm::vec3 Transform::inv_apply(const glm::vec3 vec, const bool do_translate, const bool do_rotate, const bool do_scale) const {
    return glm::xyz(inv_matrix(do_translate, do_rotate, do_scale) * glm::vec4(vec, 1));
}

glm::vec3 Transform::translated(const glm::vec3 vec) const {
    return glm::xyz(matrix(true, false, false) * glm::vec4(vec, 1));
}

glm::vec3 Transform::inv_translated(const glm::vec3 vec) const {
    return glm::xyz(inv_matrix(true, false, false) * glm::vec4(vec, 1));
}


glm::vec3 Transform::rotated(const glm::vec3 vec) const {
    return glm::xyz(matrix(false, true, false) * glm::vec4(vec, 1));
}

glm::vec3 Transform::inv_rotated(const glm::vec3 vec) const {
    return glm::xyz(inv_matrix(false, true, false) * glm::vec4(vec, 1));
}


glm::vec3 Transform::scaled(const glm::vec3 vec) const {
    return glm::xyz(matrix(false, false, true) * glm::vec4(vec, 1));
}

glm::vec3 Transform::inv_scaled(const glm::vec3 vec) const {
    return glm::xyz(inv_matrix(false, false, true) * glm::vec4(vec, 1));
}


glm::vec3 Transform::get_position() const {
    return translated(glm::vec3(0, 0, 0));
}

glm::vec3 Transform::get_scale() const {
    return scaled(glm::vec3(0, 0, 0));
}


glm::vec3 Transform::forward(const bool do_scale) const {
    return apply(glm::vec3(0, 1, 0), false, true, do_scale);
}

glm::vec3 Transform::right(const bool do_scale) const {
    return apply(glm::vec3(1, 0, 0), false, true, do_scale);
}

glm::vec3 Transform::up(const bool do_scale) const {
    return apply(glm::vec3(0, 0, 1), false, true, do_scale);
}


glm::vec3 Transform::forward_end(const bool do_scale) const {
    return apply(glm::vec3(0, 1, 0), true, true, do_scale);
}

glm::vec3 Transform::right_end(const bool do_scale) const {
    return apply(glm::vec3(1, 0, 0), true, true, do_scale);
}

glm::vec3 Transform::up_end(const bool do_scale) const {
    return apply(glm::vec3(0, 0, 1), true, true, do_scale);
}