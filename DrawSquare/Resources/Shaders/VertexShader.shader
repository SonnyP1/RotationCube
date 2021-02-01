#version 460 core

layout(location = 0) in vec3 AttribPos;
out vec3 aPos;
uniform mat4 ModelMatrix;

void main()
{
	gl_Position = ModelMatrix * vec4(AttribPos, 1.0);
	aPos = AttribPos;
}