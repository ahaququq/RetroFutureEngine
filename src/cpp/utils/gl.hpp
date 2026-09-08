#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "utils/log.hpp"

#define GCALL(call) \
    while (glGetError()) {}; \
    (call); \
    auto er = glGetError(); \
    while (er) {\
        warn("Error in { " + std::string{#call} + " }: " + std::to_string(er)); \
        er = glGetError(); \
    }