#pragma once

#include "utils/gl.hpp"

#include <string>
#include <vector>

#include "graphics/shader.hpp"
#include "window.hpp"

class program {
private:
    GLuint program_handle;
    struct shader_ref {
        shader& ref;
		// ReSharper disable once CppNonExplicitConvertingConstructor
		shader_ref(shader& sh): ref(sh) {}
    };
    std::vector<shader_ref> shaders;
    bool linked = false;
public:
    window& ctx;

	explicit program(window& context);
    program(const program &) = delete;
    program(program&&) = default;
    ~program();

    void addShader(shader& sh);
    void clearShaders();
    bool link();
    void use() const;
    [[nodiscard]] GLint getUniformLocation(const std::string &name) const;
    [[nodiscard]] GLint getAttribLocation(const std::string &name) const;
};