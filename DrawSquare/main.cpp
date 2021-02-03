#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stbi_image.h>
#include <Shader.h>
#include <Camera.h>
//use mouse movement to control viewing angle
//make a class called camera that handles everything about camera movement
//glfwGetCursorPosCallback(window,func);


#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

Camera camera;

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
	camera.SetWindow(window);
	gladLoadGLLoader(GLADloadproc(glfwGetProcAddress));

	float vertices[]
	{
		//position           //UV        
		 -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	Shader VertexShader("Resources/Shaders/VertexShader.shader",GL_VERTEX_SHADER);
	Shader FragShader("Resources/Shaders/FragmentShader.shader", GL_FRAGMENT_SHADER);

	int success = false;
	glGetShaderiv(VertexShader.GetShaderID(), GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char ComplieMessage[512];
		glGetShaderInfoLog(VertexShader.GetShaderID(), 512, nullptr, ComplieMessage);
		std::cout <<"compile error: " << ComplieMessage << std::endl;
	}

	unsigned int Program = glCreateProgram();
	glAttachShader(Program,VertexShader.GetShaderID());
	glAttachShader(Program,FragShader.GetShaderID());
	glLinkProgram(Program);
	glUseProgram(Program);

	glDeleteShader(VertexShader.GetShaderID());
	glDeleteShader(FragShader.GetShaderID());

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

	//telling VBO the first location is 3 floats
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)0);
	//Another location of the number 1, it has 2 floats
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)(sizeof(float)*3));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	unsigned int texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texture);

	int width, height, comp;
	stbi_set_flip_vertically_on_load(true);
	unsigned char*data = stbi_load("Resources/Textures/killerbean.jpg",&width,&height,&comp,0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);

	int imageTexCoord = glGetUniformLocation(Program, "Texture");
	glUniform1i(imageTexCoord, 0);

	glm::mat4 ModelMatrix(1.f);
	glEnable(GL_DEPTH_TEST);
	int modelMatrixLoc = glGetUniformLocation(Program, "ModelMatrix");
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.f, 0.f, -3.f));
	float RotateSpeed = 10.f;
	float previousTime = glfwGetTime();

	float AspectRatio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
	int ProjectMatrixLoc = glGetUniformLocation(Program, "ProjectMatrix");
	glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.f),AspectRatio,0.01f,1000.f);

	int ViewMatrixLoc = glGetUniformLocation(Program,"ViewMatrix");

	while (!glfwWindowShouldClose(window))
	{
		float DeltaTime = glfwGetTime() - previousTime;
		previousTime = glfwGetTime();
		glClearColor(0.6f,0.4f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		

		camera.Update(DeltaTime);
		

		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(RotateSpeed * DeltaTime), glm::vec3(1.f, 1.f, 1.f));
		glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		
		glUniformMatrix4fv(ProjectMatrixLoc,1,GL_FALSE,glm::value_ptr(ProjectionMatrix));

		glUniformMatrix4fv(ViewMatrixLoc, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));

		glDrawArrays(GL_TRIANGLES, 0, 12*3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}