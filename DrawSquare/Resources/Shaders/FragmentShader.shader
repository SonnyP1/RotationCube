#version 460 core

out vec4 FinalColor;
in vec3 aPos;
void main()
{
	vec4 ColorOffset = vec4(aPos, 0);
	FinalColor = ColorOffset + vec4(0.2, 0.5, 0.6, 1.0);
}