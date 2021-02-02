#version 460 core

layout(location = 0) in vec3 AttribPos;
layout(location = 1) in vec2 AttribTexCoord;
out vec3 aPos;
out vec2 TexCoord;
uniform mat4 ModelMatrix;
uniform mat4 ProjectMatrix;
uniform mat4 ViewMatrix;
void main()
{
	gl_Position = ProjectMatrix * ViewMatrix * ModelMatrix * vec4(AttribPos, 1.0);
	aPos = AttribPos;
	TexCoord = AttribTexCoord;
}