#include "program.hpp"

#include "utils/log.hpp"
#include "utils/files.hpp"

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

	char* log = new char[length];
	glGetProgramInfoLog(program_handle, length, &length, log);

	fail(std::string{"Program link failure: \n"} + log);

	delete[] log;
	linked = false;

	return false;
}

void program::use() {
	ctx.makeContextCurrent();
	if (!linked) {
		fail("Program not linked!");
		throw "";
	}
	glUseProgram(program_handle);
}