#pragma once

#include "utils/gl.hpp"
#include "window.hpp"

#include <vector>

class buffer {
private:
    GLuint handle;
    GLenum bount_to;
public:
    window& ctx;

    buffer(window& context);
    ~buffer();

    void bind(GLenum target);

    template <typename T>
    void data(const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW) {
        glBufferData(bount_to, data.size() * sizeof(data[0]), &data[0], usage);
    };

    template <typename T>
    void data(GLenum target, const std::vector<T>& data, GLenum usage = GL_STATIC_DRAW) {
        bind(target);
        glBufferData(target, data.size() * sizeof(data[0]), &data[0], usage);
    };
};