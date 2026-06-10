#version 120

attribute vec4 position;
attribute vec4 color;
//layout (location = 1) in vec3 color;
//out vec3 outColor;
uniform mat4 model_view_mat;
void main() {
	gl_Position = model_view_mat * position;
	// gl_Position = position;
	// gl_FrontColor = color;
}