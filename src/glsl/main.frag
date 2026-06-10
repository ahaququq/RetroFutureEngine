#version 120

//in vec3 outColor;
//out vec4 color;
void main() {
	//gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	//color = vec4(outColor, 1.0f);
	// gl_FragColor = vec4(floor(gl_Color.xyz * 2.0 + 0.5) / 2.0, 1.0);
	// gl_FragColor.xyz *= 1.0 - abs(1.0 - pow(gl_FragCoord.w + 0.75, 10.0));
	gl_FragColor = vec4(0.25, 0.5, 1.0, 1.0);
	gl_FragColor = vec4(1.0);
	gl_FragColor *= abs(1.0 - pow(gl_FragCoord.z + 0.5, 5.0));
}