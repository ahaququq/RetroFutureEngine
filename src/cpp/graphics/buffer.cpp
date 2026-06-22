#include "buffer.hpp"

buffer::buffer(window& context) : bound_to(0), ctx(context) {
	glGenBuffers(1, &handle);
}

buffer::~buffer() {
    glDeleteBuffers(1, &handle);
}

void buffer::bind(const GLenum target) {
    bound_to = target;
    glBindBuffer(target, handle);
}