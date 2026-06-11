#include "buffer.hpp"

buffer::buffer(window& context): ctx(context) {
    glGenBuffers(1, &handle);
}

buffer::~buffer() {
    glDeleteBuffers(1, &handle);
}

void buffer::bind(GLenum target) {
    bount_to = target;
    glBindBuffer(target, handle);
}