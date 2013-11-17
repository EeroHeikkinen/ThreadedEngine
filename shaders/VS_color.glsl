#version 330 core

layout(location = 0) in vec3 _position;
layout(location = 1) in vec3 _color;

uniform mat4 MVP;

out vec3 color_;

void main(void) {
	gl_Position = MVP * vec4(_position, 1.0f);
	color_ = _color;
}
