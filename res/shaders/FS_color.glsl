#version 330 core

in vec3 color_;

out vec3 color;

void main(void) {
	color = vec3(color_);
}
