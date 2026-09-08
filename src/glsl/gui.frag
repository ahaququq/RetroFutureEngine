#version 120

//in vec3 outColor;
//out vec4 color;
void main() {
	// gl_FragColor = vec4(gl_Color.xyz, 1.0);
	gl_FragColor = gl_Color;
	gl_FragColor.w = 1.0;
	// gl_FragColor = vec4(1.0, 0.5, 0.25, 1.0);
}