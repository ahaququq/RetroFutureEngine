#pragma once

#include "glfw_context.hpp"
#include "window.hpp"
#include "graphics/program.hpp"
#include "utils/files.hpp"
#include "gui/GuiRenderer.hpp"

class engine {
private:
	glfw_context ctx{};
	window main_window = window(ctx, 640, 640, "RetroFutureEngine");
	program material = program(main_window, "material");
	shader vertex_shader = shader(material, GL_VERTEX_SHADER, load_file("src/glsl/main.vert"), "main.vert");
	shader fragment_shader = shader(material, GL_FRAGMENT_SHADER, load_file("src/glsl/main.frag"), "main.frag");
	GuiRenderer gui_mgr = GuiRenderer(main_window);
public:
	engine();
	engine(const engine &) = delete;
	~engine();
	
	int main();
};