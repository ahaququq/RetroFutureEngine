#pragma once

#include "utils/glm.hpp"

class camera {
public:
    glm::vec3 pos;
    glm::quat rot;
    float fov;

    camera(float f = 45.0, glm::vec3 p = {0, 0, 0}, glm::quat r = glm::quat_identity<float, glm::packed_highp>());

    glm::mat4 world_to_camera() const;
    glm::mat4 camera_to_world() const;
    glm::mat4 camera_rotation() const;
    glm::vec3 rot_camera_to_world(glm::vec3 vec) const;
    glm::vec3 rot_camera_to_world_z_only(glm::vec3 vec) const;
    glm::vec3 up_vector(bool lock = true) const;
    bool upside_down() const;
    glm::mat4 camera_inverse_rotation() const;
    glm::mat4 camera_to_view(glm::ivec2 viewport) const;
    void rotate(glm::vec3 axies);
};