#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

int main()
{
	//Initializes glfw variable and assign return value to check if initialization was a success
	bool initErr = glfwInit();

	//Checks to see if initialization worked
	if (! initErr) { return 1; }

	return 0;
}