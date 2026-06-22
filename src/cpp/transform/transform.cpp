#include "transform.hpp"

glm::mat4 transform::translation() const {
    return glm::identity<glm::mat4>();
}

glm::mat4 transform::rotation() const {
    return glm::identity<glm::mat4>();
}

glm::mat4 transform::scale() const {
    return glm::identity<glm::mat4>();
}



bool transform::has_translation() const {
    return false;
}

bool transform::has_rotation() const {
    return false;
}

bool transform::has_scale() const {
    return false;
}



bool transform::can_translate() const {
    return false;
}

bool transform::can_rotate() const {
    return false;
}

bool transform::can_scale() const {
    return false;
}


glm::mat4 transform::matrix(const bool do_translate, const bool do_rotate, const bool do_scale) const {
    auto result = glm::identity<glm::mat4>();
    if (do_scale) result = scale() * result;
    if (do_rotate) result = rotation() * result;
    if (do_translate) result = translation() * result;
    return result;
}

glm::mat4 transform::inv_matrix(const bool do_translate, const bool do_rotate, const bool do_scale) const {
    return glm::inverse(matrix(do_translate, do_rotate, do_scale));
}

glm::vec3 transform::apply(const glm::vec3 vec, const bool do_translate, const bool do_rotate, const bool do_scale) const {
    return glm::xyz(matrix(do_translate, do_rotate, do_scale) * glm::vec4(vec, 1));
}

glm::vec3 transform::inv_apply(const glm::vec3 vec, const bool do_translate, const bool do_rotate, const bool do_scale) const {
    return glm::xyz(inv_matrix(do_translate, do_rotate, do_scale) * glm::vec4(vec, 1));
}

glm::vec3 transform::translated(const glm::vec3 vec) const {
    return glm::xyz(matrix(true, false, false) * glm::vec4(vec, 1));
}

glm::vec3 transform::inv_translated(const glm::vec3 vec) const {
    return glm::xyz(inv_matrix(true, false, false) * glm::vec4(vec, 1));
}


glm::vec3 transform::rotated(const glm::vec3 vec) const {
    return glm::xyz(matrix(false, true, false) * glm::vec4(vec, 1));
}

glm::vec3 transform::inv_rotated(const glm::vec3 vec) const {
    return glm::xyz(inv_matrix(false, true, false) * glm::vec4(vec, 1));
}


glm::vec3 transform::scaled(const glm::vec3 vec) const {
    return glm::xyz(matrix(false, false, true) * glm::vec4(vec, 1));
}

glm::vec3 transform::inv_scaled(const glm::vec3 vec) const {
    return glm::xyz(inv_matrix(false, false, true) * glm::vec4(vec, 1));
}


glm::vec3 transform::get_position() const {
    return translated(glm::vec3(0, 0, 0));
}

glm::vec3 transform::get_scale() const {
    return scaled(glm::vec3(0, 0, 0));
}


glm::vec3 transform::forward(const bool do_scale) const {
    return apply(glm::vec3(0, 1, 0), false, true, do_scale);
}

glm::vec3 transform::right(const bool do_scale) const {
    return apply(glm::vec3(1, 0, 0), false, true, do_scale);
}

glm::vec3 transform::up(const bool do_scale) const {
    return apply(glm::vec3(0, 0, 1), false, true, do_scale);
}


glm::vec3 transform::forward_end(const bool do_scale) const {
    return apply(glm::vec3(0, 1, 0), true, true, do_scale);
}

glm::vec3 transform::right_end(const bool do_scale) const {
    return apply(glm::vec3(1, 0, 0), true, true, do_scale);
}

glm::vec3 transform::up_end(const bool do_scale) const {
    return apply(glm::vec3(0, 0, 1), true, true, do_scale);
}