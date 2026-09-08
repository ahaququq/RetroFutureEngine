#include "buffer.hpp"
#include "utils/log.hpp"

buffer::buffer(window& context) : bound_to(0), ctx(context) {
	GCALL(glGenBuffers(1, &handle));
}

buffer::~buffer() {
    GCALL(glDeleteBuffers(1, &handle));
}

void buffer::bind(const GLenum target) {
    bound_to = target;
    GCALL(glBindBuffer(target, handle));
}

void buffer::debugInfo() {
    info("Buffer #" + std::to_string(handle));
}