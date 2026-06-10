#pragma once

#include "utils/gl.hpp"

#include <vector>
#include <string>

#include "window.hpp"

class program;

class shader {
private:
    GLuint handle;
    std::vector<std::string> sources;
    bool compiled = false;
public:
    std::string name;
    window& ctx;

    shader(window& context, GLenum type);
    shader(window& context, GLenum type, std::string source, const std::string& id = "");
    shader(program& add_to, GLenum type, std::string source, const std::string& id = "");
    shader(const shader &) = delete;
    shader(shader&&) = default;
    ~shader();

    static shader fromFile(window& context, GLenum type, const std::string& name);
    static shader fromFile(program& add_to, GLenum type, const std::string& name);

    void clearSources();
    void addSource(std::string source);
    void addFile(std::string file);
    
    bool compile();
    void attach(GLuint program) const;
};