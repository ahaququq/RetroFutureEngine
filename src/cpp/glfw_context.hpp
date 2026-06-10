#pragma once

class glfw_context {
public:
	glfw_context();
	glfw_context(const glfw_context &) = delete;
	~glfw_context();

	void pollEvents();
};