#pragma once

#include "utils/glm.hpp"
#include "window.hpp"
#include "graphics/buffer.hpp"
#include "graphics/program.hpp"
#include "utils/files.hpp"
#include <vector>

class GuiRenderer {
public:
    struct vertex {
        glm::vec3 pos; // X, Y, layer
        glm::vec4 col; // R, G, B, A
    };
    
    struct triangle {
        vertex a, b, c;
    };

    std::vector<triangle> triangles;

    window &parent_window;
    buffer pos_buffer = buffer(parent_window);
    std::vector<glm::vec3> pos;
    buffer col_buffer = buffer(parent_window);
    std::vector<glm::vec4> col;
    buffer idx_buffer = buffer(parent_window);
    bool data_valid = false;
    program material = program(parent_window, "gui");
    shader vertex_shader = shader(material, GL_VERTEX_SHADER, load_file("src/glsl/gui.vert"), "gui.vert");
	shader fragment_shader = shader(material, GL_FRAGMENT_SHADER, load_file("src/glsl/gui.frag"), "gui.frag");

    GuiRenderer(window &parent);

    void clear();
    void buildData();
    void render();
    void debugInfo();

    void addTriangle(triangle tri);
    void addTriangle(vertex a, vertex b, vertex c);
    void addTriangle(
        glm::vec3 a, glm::vec3 b, glm::vec3 c, 
        glm::vec4 col = {0.5f, 0.5f, 0.5f, 0.5f}
    );

    void addTriangle(
        glm::vec2 a, glm::vec2 b, glm::vec2 c, 
        glm::vec4 col = {0.5f, 0.5f, 0.5f, 0.5f},
        float layer = 0.5
    );

    void addRect(
        glm::vec2 center, glm::vec2 size, 
        glm::vec4 col = {0.5f, 0.5f, 0.5f, 0.5f},
        float layer = 0.5, float rot = 0
    );

};