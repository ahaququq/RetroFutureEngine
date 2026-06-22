#include "program.hpp"

#include <stdexcept>

#include "utils/log.hpp"

program::program(window& context): ctx(context) {
	ctx.makeContextCurrent();
	program_handle = glCreateProgram();
}

program::~program() {
	ctx.makeContextCurrent();
	glDeleteProgram(program_handle);
}

void program::addShader(shader& sh) {
	shaders.emplace_back(sh);
	linked = false;
}

void program::clearShaders() {
	shaders.clear();
	linked = false;
}

bool program::link() {
	if (linked) {
		info("Shader program already linked.");
		return true;
	}
	info("Preparing shaders:");
	ctx.makeContextCurrent();

	for (shader_ref& shader: shaders) {
		if (!shader.ref.compile()) {
			fail("Shader compilation failed, skipping linking");
			linked = false;
			return false;
		}
		shader.ref.attach(program_handle);
	}

	glLinkProgram(program_handle);

	{
		int status;
		glGetProgramiv(program_handle, GL_LINK_STATUS, &status);
		if (status) {
			ok("Program linked successfully");
			linked = true;
			return true;
		}
	}

	int length;
	glGetProgramiv(program_handle, GL_INFO_LOG_LENGTH, &length);

	const auto log = new char[length];
	glGetProgramInfoLog(program_handle, length, &length, log);

	fail(std::string{"Program link failure: \n"} + log);

	delete[] log;
	linked = false;

	return false;
}

void program::use() const {
	ctx.makeContextCurrent();
	if (!linked) {
		fail("Program not linked!");
		throw std::runtime_error("Program not linked when calling program::use()");
	}
	glUseProgram(program_handle);
}

GLint program::getUniformLocation(const std::string &name) const {
	return glGetUniformLocation(program_handle, name.c_str());
}

GLint program::getAttribLocation(const std::string &name) const {
	return glGetAttribLocation(program_handle, name.c_str());
}
