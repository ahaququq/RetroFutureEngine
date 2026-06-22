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


glm::mat4 transform::matrix(bool do_translate, bool do_rotate, bool do_scale) const {
    glm::mat4 result = glm::identity<glm::mat4>();
    if (do_scale) result = scale() * result;
    if (do_rotate) result = rotation() * result;
    if (do_translate) result = translation() * result;
    return result;
}

glm::mat4 transform::inv_matrix(bool do_translate, bool do_rotate, bool do_scale) const {
    return glm::inverse(matrix(do_translate, do_rotate, do_scale));
}

glm::vec3 transform::apply(glm::vec3 vec, bool do_translate, bool do_rotate, bool do_scale) const {
    return glm::xyz(matrix(do_translate, do_rotate, do_scale) * glm::vec4(vec, 1));
}

glm::vec3 transform::inv_apply(glm::vec3 vec, bool do_translate, bool do_rotate, bool do_scale) const {
    return glm::xyz(inv_matrix(do_translate, do_rotate, do_scale) * glm::vec4(vec, 1));
}

glm::vec3 transform::translated(glm::vec3 vec) const {
    return glm::xyz(matrix(true, false, false) * glm::vec4(vec, 1));
}

glm::vec3 transform::inv_translated(glm::vec3 vec) const {
    return glm::xyz(inv_matrix(true, false, false) * glm::vec4(vec, 1));
}


glm::vec3 transform::rotated(glm::vec3 vec) const {
    return glm::xyz(matrix(false, true, false) * glm::vec4(vec, 1));
}

glm::vec3 transform::inv_rotated(glm::vec3 vec) const {
    return glm::xyz(inv_matrix(false, true, false) * glm::vec4(vec, 1));
}


glm::vec3 transform::scaled(glm::vec3 vec) const {
    return glm::xyz(matrix(false, false, true) * glm::vec4(vec, 1));
}

glm::vec3 transform::inv_scaled(glm::vec3 vec) const {
    return glm::xyz(inv_matrix(false, false, true) * glm::vec4(vec, 1));
}


glm::vec3 transform::get_position() const {
    return translated(glm::vec3(0, 0, 0));
}

glm::vec3 transform::get_scale() const {
    return scaled(glm::vec3(0, 0, 0));
}


glm::vec3 transform::forward(bool do_scale) const {
    return apply(glm::vec3(0, 1, 0), false, true, do_scale);
}

glm::vec3 transform::right(bool do_scale) const {
    return apply(glm::vec3(1, 0, 0), false, true, do_scale);
}

glm::vec3 transform::up(bool do_scale) const {
    return apply(glm::vec3(0, 0, 1), false, true, do_scale);
}


glm::vec3 transform::forward_end(bool do_scale) const {
    return apply(glm::vec3(0, 1, 0), true, true, do_scale);
}

glm::vec3 transform::right_end(bool do_scale) const {
    return apply(glm::vec3(1, 0, 0), true, true, do_scale);
}

glm::vec3 transform::up_end(bool do_scale) const {
    return apply(glm::vec3(0, 0, 1), true, true, do_scale);
}