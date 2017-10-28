
#version 460 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec4 color;
out vec4 vColor;

void main(void) {
	gl_Position = vec4(pos, 0.5f, 1.0f);
	vColor = color;
}