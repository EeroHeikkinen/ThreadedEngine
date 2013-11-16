#version 330 core

in vec2 uv_;
in vec3 normal_;

out vec3 color;

void main(void) {
	color = vec3(normal_);
}
