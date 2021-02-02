#version 460 core

out vec4 FinalColor;
in vec3 aPos;
in vec2 TexCoord;

uniform sampler2D Texture;
void main()
{
	vec4 ColorOffset = vec4(aPos, 0);
	FinalColor = texture(Texture, TexCoord);
}