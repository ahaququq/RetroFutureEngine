#pragma once

#include "glfw_context.hpp"
#include "window.hpp"
#include "graphics/program.hpp"
#include "utils/files.hpp"

class engine {
private:
	glfw_context ctx{};
	window main_window = window(ctx, 640, 480, "RetroFutureEngine");
	program material = program(main_window);
	shader vertex = shader(material, GL_VERTEX_SHADER, load_file("src/glsl/main.vert"), "main.vert");
	shader fragment = shader(material, GL_FRAGMENT_SHADER, load_file("src/glsl/main.frag"), "main.frag");
public:
	engine();
	engine(const engine &) = delete;
	~engine();
	
	int main();
};