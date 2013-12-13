#version 330 core

layout(location = 0) in vec3 _position;
//layout(location = 1) in vec3 _color;

//out vec3 color;

void main(void) {
	gl_Position = vec4(_position, 1.0f);
	//color = _color;
}
