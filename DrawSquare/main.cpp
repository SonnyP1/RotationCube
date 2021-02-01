#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

std::string GetSourceString(const std::string& Dir)
{
	std::ifstream SourceFile{Dir};
	std::string ShaderScrString;
	std::string Read;
	while (std::getline(SourceFile, Read))
	{
		ShaderScrString += Read;
		ShaderScrString += '\n';
	}

	return ShaderScrString;
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"DrawSquare",nullptr,nullptr);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));

	float vertices[]
	{
		-0.5f,-0.5f,-0.5f, // triangle 1 : begin
		-0.5f,-0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f, // triangle 1 : end

		0.5f, 0.5f,-0.5f, // triangle 2 : begin
		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f, // triangle 2 : end

		0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,

		0.5f, 0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,

		-0.5f,-0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,

		0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		-0.5f,-0.5f,-0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f,-0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,

		0.5f, 0.5f, 0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f,-0.5f,

		0.5f,-0.5f,-0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f,-0.5f, 0.5f,

		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f,-0.5f,

		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		-0.5f, 0.5f, 0.5f,

		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f,-0.5f, 0.5f
	};

	std::string VertexShaderSrcStr = GetSourceString("Resources/Shaders/VertexShader.shader");
	std::string FragmentShaderSrcStr = GetSourceString("Resources/Shaders/FragmentShader.shader");

	const char* VertexSrcRaw = VertexShaderSrcStr.c_str();
	unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader,1,&VertexSrcRaw,nullptr);
	glCompileShader(VertexShader);

	const char* FragmentSrcRaw = FragmentShaderSrcStr.c_str();
	unsigned int FragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragShader,1,&FragmentSrcRaw,nullptr);
	glCompileShader(FragShader);

	int success = false;
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char ComplieMessage[512];
		glGetShaderInfoLog(VertexShader, 512, nullptr, ComplieMessage);
		std::cout <<"compile error: " << ComplieMessage << std::endl;
	}

	unsigned int Program = glCreateProgram();
	glAttachShader(Program,VertexShader);
	glAttachShader(Program,FragShader);
	glLinkProgram(Program);
	glUseProgram(Program);

	glDeleteShader(VertexShader);
	glDeleteShader(FragShader);

	int LinkSuccess = false;
	glGetProgramiv(Program, GL_LINK_STATUS, &LinkSuccess);
	if (!LinkSuccess)
	{
		std::cout << "linking error" << std::endl;
	}

	unsigned int VAO;
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);
	glEnableVertexAttribArray(0);

	glm::mat4 ModelMatrix(1.f);
	
	int modelMatrixLoc = glGetUniformLocation(Program, "ModelMatrix");
	float RotateSpeed = 2.f;
	
	float previousTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		float DeltaTime = glfwGetTime() - previousTime;
		previousTime = glfwGetTime();
		glClearColor(0.6f,0.4f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(RotateSpeed * DeltaTime), glm::vec3(1.f, 1.f, 1.f));

		glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		
		glDrawArrays(GL_TRIANGLES, 0, 12*3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}