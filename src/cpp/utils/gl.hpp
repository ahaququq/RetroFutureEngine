#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "utils/log.hpp"

// Comment to disable debugging
#define GL_DEBUG

#ifdef GL_DEBUG
#define GCALL(call) \
    beforeGL(); \
    (call); \
    afterGL(#call);
#else
#define GCALL(call) call
#endif

void beforeGL();
void afterGL(std::string call);