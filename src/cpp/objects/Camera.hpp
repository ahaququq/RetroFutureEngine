#pragma once

#include "transform/Transform_Pxyz_Rxyz.hpp"
#include "utils/glm.hpp"

class Camera {
public:
    Transform_Pxyz_Rxyz transform;
    float fov;

    Camera(float f = 45.0, Transform_Pxyz_Rxyz transform = {});

    [[nodiscard]] glm::mat4 world_to_camera() const;
    [[nodiscard]] glm::mat4 camera_to_world() const;
    [[nodiscard]] glm::mat4 camera_rotation() const;
    [[nodiscard]] glm::vec3 rot_camera_to_world(glm::vec3 vec) const;
    [[nodiscard]] glm::vec3 rot_camera_to_world_z_only(glm::vec3 vec) const;
    [[nodiscard]] glm::vec3 up_vector(bool lock = true) const;
    [[nodiscard]] bool upside_down() const;
    [[nodiscard]] glm::mat4 camera_inverse_rotation() const;
    [[nodiscard]] glm::mat4 camera_to_view(glm::ivec2 viewport) const;
    void rotate(glm::vec3 axies);
};