
#version 450 core

layout (location = 0) in vec2 pos;

void main(void) {
	gl_Position = vec4(pos, 0.5f, 1.0f);
}