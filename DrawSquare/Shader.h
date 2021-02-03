#pragma once
#include <string>
class Shader
{
public:
	Shader(const std::string& SrcDir, unsigned int Type);
	unsigned int GetShaderID() const
	{return m_ShaderID;}

private:
	std::string GetSourceString(const std::string& Dir);
private:
	unsigned int m_ShaderID;
};