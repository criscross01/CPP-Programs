#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
	//Initializes glfw variable and assign return value to check if initialization was a success
	bool initErr = glfwInit();

	//Checks to see if initialization worked
	if (!initErr) { return -1; }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Makes window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW test", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Makes the current context of the thread the window
	glfwMakeContextCurrent(window);

	//True if GLAD not initialized
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Sets up the viewport
	glViewport(0, 0, 800, 600);

	//Sets up to where everytime the window is resized, it calls the framebuffer_size_callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	float vertices[] = {
		-0.5f,-0.5f, 0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
		"}\n\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}





	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Gets input
		processInput(window);

		//Rendering
		glClearColor(0.3f, 1.0f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Check and call events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);		
	}



	glfwTerminate();

	return 0;
}

//Called when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//Processes input
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}