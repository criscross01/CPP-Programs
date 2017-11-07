#include <glad/glad.h>
#include <GLFW\glfw3.h>

#include <iostream>
#include <fstream>

#include "shader.h"
#include "stb_image.h"

using namespace std;

int width{ 800 }, height{ 600 };
const char* title{ "What I saw dude" };

float vertices[] = {
	-0.5f,-0.5f,0.0f,
	 0.5f,-0.5f,0.0f,
	 0.0f, 0.5f,0.0f
};

void glFramebufferSizeCallback(GLFWwindow* window, int width, int height);
void procesInput(GLFWwindow* window);

int main()
{
	if (!glfwInit())
	{
		cerr << "GLFW INITIALIZATION FAILED!" << endl;
		cin.get();
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		cerr << "WINDOW IS NULL" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cerr << "LOADING GLAD FAILED" << endl;
		return -1;
	}
	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(window, glFramebufferSizeCallback);

	Shader shader("vertexShader.txt","fragmentShader.txt");

	int tWidth, tHeight, nrChannels;

	unsigned char *data = stbi_load("Container.jpg", &width, &height, &nrChannels, 0);

	unsigned int VBO, VAO; 

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		procesInput(window);

		glClearColor(0.26f, 0.93f, 0.75f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void glFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void procesInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}