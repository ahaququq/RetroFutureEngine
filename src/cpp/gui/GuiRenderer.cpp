#include "GuiRenderer.hpp"

#include "transform/Transform_Ry.hpp"
#include "utils/log.hpp"

GuiRenderer::GuiRenderer(
    window &parent
): parent_window(parent) {
    material.link();
    info("Pos: #" + std::to_string(material.getAttribLocation("position")));
    info("Col: #" + std::to_string(material.getAttribLocation("color")));
}

void GuiRenderer::clear() {
    triangles.clear();
    data_valid = false;
}

void GuiRenderer::buildData() {
    if (!data_valid) { // Keep buffer if nothing changed
        pos.clear(); col.clear();
        pos.resize(triangles.size() * 3, {0, 0, 0});
        col.resize(triangles.size() * 3, {0, 0, 0, 0});
        // data_buffer.data(triangles, GL_ARRAY_BUFFER);
        int i = 0;
        for (auto tri : triangles) {
            pos[i]   = tri.a.pos;
            col[i++] = tri.a.col;
            pos[i]   = tri.b.pos;
            col[i++] = tri.b.col;
            pos[i]   = tri.c.pos;
            col[i++] = tri.c.col;
        }

        pos_buffer.data(GL_ARRAY_BUFFER, pos);
        col_buffer.data(GL_ARRAY_BUFFER, col);

        data_valid = true;
    }
}

void GuiRenderer::render() {
    GCALL(glDisable(GL_DEPTH_TEST));
    // GCALL(glDisable(GL_DEPTH_CLAMP));

    if (triangles.empty()) return;
    buildData();
    // data_buffer.bind(GL_ARRAY_BUFFER);
    pos_buffer.bind(GL_ARRAY_BUFFER);
    GCALL(glEnableVertexAttribArray(material.getAttribLocation("position")));
	GCALL(glVertexAttribPointer(material.getAttribLocation("position"), 3, GL_FLOAT, true, 0, nullptr));
    col_buffer.bind(GL_ARRAY_BUFFER);
    GCALL(glEnableVertexAttribArray(material.getAttribLocation("color")));
	GCALL(glVertexAttribPointer(material.getAttribLocation("color"), 4, GL_FLOAT, true, 0, nullptr));
    material.use();

    GCALL(glDrawArrays(GL_TRIANGLES, 0, triangles.size() * 3));
    
    // GCALL(glEnable(GL_DEPTH_CLAMP));
    GCALL(glEnable(GL_DEPTH_TEST));
}

void GuiRenderer::debugInfo() {
    info("GuiRenderer.pos = {");
    for (int i = 0; i < pos.size(); i++) {
        info("\t" + std::to_string(i) + ":\t" + glm::to_string(pos[i]));
    }
    info("}");

    info("GuiRenderer.col = {");
    for (int i = 0; i < col.size(); i++) {
        info("\t" + std::to_string(i) + ":\t" + glm::to_string(col[i]));
    }
    info("}");
}

void GuiRenderer::addTriangle(triangle tri) {
    triangles.emplace_back(tri);
    data_valid = false;
}

void GuiRenderer::addTriangle(
    vertex a,
    vertex b,
    vertex c
) {
    addTriangle(triangle{a, b, c});
}

void GuiRenderer::addTriangle(
    glm::vec3 a,
    glm::vec3 b,
    glm::vec3 c,
    glm::vec4 col
) {
    addTriangle(
        vertex{a, col}, 
        vertex{b, col}, 
        vertex{c, col}
    );
}

void GuiRenderer::addTriangle(
    glm::vec2 a, 
    glm::vec2 b, 
    glm::vec2 c,
    glm::vec4 col,
    float layer
) {
    addTriangle(
        vertex{{a.x, a.y, layer}, col},
        vertex{{b.x, b.y, layer}, col},
        vertex{{c.x, c.y, layer}, col}
    );
}

void GuiRenderer::addRect(
    glm::vec2 center, glm::vec2 size,
    glm::vec4 col,
    float layer, float rot
) {
    vertex a, b, c, d;
    a.col = b.col = c.col = d.col = col;
    a.pos = b.pos = c.pos = d.pos = {center.x, center.y, layer};
    size /= 2;
    if (rot == 0) {
        a.pos += glm::vec3{-size.x, -size.y, 0};
        b.pos += glm::vec3{ size.x, -size.y, 0};
        c.pos += glm::vec3{-size.x,  size.y, 0};
        d.pos += glm::vec3{ size.x,  size.y, 0};
    } else {
        Transform_Ry rotate(rot);
        a.pos += rotate.apply({-size.x, -size.y, 0});
        b.pos += rotate.apply({ size.x, -size.y, 0});
        c.pos += rotate.apply({-size.x,  size.y, 0});
        d.pos += rotate.apply({ size.x,  size.y, 0});
    }
    addTriangle(a, b, c);
    addTriangle(c, b, d);
}