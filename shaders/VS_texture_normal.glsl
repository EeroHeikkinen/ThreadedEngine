#version 330 core

layout(location = 0) in vec3 _position;
layout(location = 1) in vec2 _uv;
layout(location = 2) in vec3 _normal;

uniform mat4 MVP;

out vec2 uv_;
out vec3 normal_;
out vec4 position_;

void main(void) {
	gl_Position = MVP * vec4(_position, 1.0f);
	uv_ = _uv;
	normal_ = _normal;
	position_ = MVP * vec4(_position, 1.0f);
}
