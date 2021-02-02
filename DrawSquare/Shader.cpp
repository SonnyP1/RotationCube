#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
Shader::Shader(const std::string& SrcDir, unsigned int Type)
	:m_ShaderID(glCreateShader(Type))
{
	std::string VertexShaderSrcStr = GetSourceString(SrcDir);
	const char* VertexSrcRaw = VertexShaderSrcStr.c_str();
	glShaderSource(m_ShaderID, 1, &VertexSrcRaw, nullptr);
	glCompileShader(m_ShaderID);
}

std::string Shader::GetSourceString(const std::string& Dir)
{
	std::ifstream SourceFile{ Dir };
	std::string ShaderScrString;
	std::string Read;
	while (std::getline(SourceFile, Read))
	{
		ShaderScrString += Read;
		ShaderScrString += '\n';
	}

	return ShaderScrString;
}
