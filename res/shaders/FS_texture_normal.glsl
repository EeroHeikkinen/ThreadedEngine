#version 330 core

in vec2 uv_;
in vec3 normal_;
in vec4 position_;

uniform sampler2D texture_;

out vec3 color;

void main(void) {
	color = texture(texture_, uv_).rgb;
}
