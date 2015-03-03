#version 330

uniform vec2 offset;
uniform vec2 scale;
uniform mat4 worldMatrix;

layout (location = 0) in vec2 position;

void main()
{
    //gl_Position = vec4(position * scale + offset, 0, 1);
	gl_Position = worldMatrix * vec4(position, 0, 1);
}