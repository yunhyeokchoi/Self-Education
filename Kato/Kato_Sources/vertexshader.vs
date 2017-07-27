#version 330

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 colorin;

out vec4 colorout;

void main()
{
	colorout = colorin;
	gl_Position = pos;
}