#include "gl.hpp"

#include <map>

const std::map<GLenum, std::string> glErrors = {
    {GL_NO_ERROR, "GL_NO_ERROR"},
    {GL_INVALID_ENUM, "GL_INVALID_ENUM"},
    {GL_INVALID_VALUE, "GL_INVALID_VALUE"},
    {GL_INVALID_OPERATION, "GL_INVALID_OPERATION"},
    {GL_INVALID_FRAMEBUFFER_OPERATION, "GL_INVALID_FRAMEBUFFER_OPERATION"},
    {GL_OUT_OF_MEMORY, "GL_OUT_OF_MEMORY"},
    {GL_STACK_UNDERFLOW, "GL_STACK_UNDERFLOW"},
    {GL_STACK_OVERFLOW, "GL_STACK_OVERFLOW"}
};

std::string glErrorToString(GLenum err) {
    auto search = glErrors.find(err);
    if (search == glErrors.end())
        return "GL_#" + std::to_string(err);
    
    return search->second;
}

void beforeGL() {
    GLenum err = glGetError();
    while(err) {
        warn("Error before GCALL: " + glErrorToString(err));
        err = glGetError();
    }
}

void afterGL(std::string call) {
    GLenum err = glGetError();
    while (err) {
        warn("Error in GLCALL(" + call + "): " + glErrorToString(err));
        err = glGetError();
    }
}