#include "shader.hpp"

#include "utils/files.hpp"
#include "utils/log.hpp"
#include "program.hpp"

shader::shader(window& context, const GLenum type): ctx(context) {
    ctx.makeContextCurrent();
    handle = glCreateShader(type);
}

shader::shader(window& context, const GLenum type, const std::string &source, const std::string& id): shader(context, type) {
    addSource(source);
    name = id;
}

shader::shader(program& add_to, const GLenum type, const std::string &source, const std::string& id):
    shader(add_to.ctx, type, source, id) 
{
    add_to.addShader(*this);
}

shader::~shader() {
    ctx.makeContextCurrent();
    glDeleteShader(handle);
}

shader shader::fromFile(window& context, const GLenum type, const std::string& name) {
    return {context, type, load_file(name), name};
}

shader shader::fromFile(program& add_to, const GLenum type, const std::string& name) {
    return {add_to, type, load_file(name), name};
}

void shader::clearSources() {
    sources.clear();
    compiled = false;
}

void shader::addSource(const std::string& source) {
    sources.emplace_back(source);
    compiled = false;
}

void shader::addFile(const std::string &file) {
    addSource(load_file(file));
}

bool shader::compile() {
    if (compiled) {
        info("Shader \"" + name + "\" (" + std::to_string(handle) + ") already compiled.");
        return true;
    }
    ctx.makeContextCurrent();
	const auto cstrs = new const char*[sources.size()];
    const auto counts = new int[sources.size()];

    busy("Attaching sources to \"" + name + "\" (" + std::to_string(handle) + ") shader...");
    for (int i = 0; i < sources.size(); i++) {
        cstrs[i] = sources[i].c_str();
        counts[i] = static_cast<int>(sources[i].size());
    }

    glShaderSource(handle, static_cast<int>(sources.size()), cstrs, counts);
    busy("Compiling \"" + name + "\" (" + std::to_string(handle) + ") shader...");
    glCompileShader(handle);

    delete[] cstrs;
    delete[] counts;

    {
        int status;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
        if (status) {
            compiled = true;
            ok("Shader \"" + name + "\" (" + std::to_string(handle) + ") compiled successfully");
            return true;
        }
    }

    int length;
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);

    const auto log = new char[length];

    glGetShaderInfoLog(handle, length, &length, log);

    fail("Shader \"" + name + "\" (" + std::to_string(handle) + ") failed to compile: \n" + log);

    delete[] log;
    compiled = false;

    return false;
}

void shader::attach(const GLuint program) const {
    ctx.makeContextCurrent();
    glAttachShader(program, handle);
}