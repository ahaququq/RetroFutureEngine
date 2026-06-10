#include "shader.hpp"

#include "utils/files.hpp"
#include "utils/log.hpp"
#include "program.hpp"

shader::shader(window& context, GLenum type): ctx(context) {
    ctx.makeContextCurrent();
    handle = glCreateShader(type);
}

shader::shader(window& context, GLenum type, std::string source, const std::string& id): shader(context, type) {
    addSource(source);
    name = id;
}

shader::shader(program& add_to, GLenum type, std::string source, const std::string& id): 
    shader(add_to.ctx, type, source, id) 
{
    add_to.addShader(*this);
}

shader::~shader() {
    ctx.makeContextCurrent();
    glDeleteShader(handle);
}

shader shader::fromFile(window& context, GLenum type, const std::string& name) {
    return shader(context, type, load_file(name), name);
}

shader shader::fromFile(program& add_to, GLenum type, const std::string& name) {
    return shader(add_to, type, load_file(name), name);
}

void shader::clearSources() {
    sources.clear();
    compiled = false;
}

void shader::addSource(std::string source) {
    sources.emplace_back(source);
    compiled = false;
}

void shader::addFile(std::string file) {
    addSource(load_file(file));
}

bool shader::compile() {
    if (compiled) {
        info("Shader already compiled.");
        return true;
    }
    ctx.makeContextCurrent();
    const char** cstrs = new const char*[sources.size()];
    int* counts = new int[sources.size()];

    busy("Attaching sources...");
    for (int i = 0; i < sources.size(); i++) {
        cstrs[i] = sources[i].c_str();
        counts[i] = sources[i].size();
    }

    glShaderSource(handle, sources.size(), cstrs, counts);
    busy("Compiling shader...");
    glCompileShader(handle);

    delete[] cstrs;
    delete[] counts;

    {
        int status;
        glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
        if (status) {
            compiled = true;
            ok("Shader compiled successfully");
            return true;
        }
    }

    int length;
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &length);

    char* log = new char[length];

    glGetShaderInfoLog(handle, length, &length, log);

    fail(std::string{"Shader compilation failure: \n"} + log);

    delete[] log;
    compiled = false;

    return false;
}

void shader::attach(GLuint program) const {
    ctx.makeContextCurrent();
    glAttachShader(program, handle);
}