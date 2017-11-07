#include "shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	const char* vertexCode;
	const char* fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	stringstream vBuffer;
	stringstream fBuffer;

	string vStringBuffer;
	string fStringBuffer;

	vShaderFile.open(vertexPath);
	vBuffer << vShaderFile.rdbuf();
	vShaderFile.close();
	vStringBuffer = vBuffer.str();
	vertexCode = vStringBuffer.c_str();

	fShaderFile.open(fragmentPath);
	fBuffer << fShaderFile.rdbuf();
	fShaderFile.close();
	fStringBuffer = fBuffer.str();
	fragmentCode = fStringBuffer.c_str();

	unsigned int vertexShader, fragmentShader;
	vertexShader   = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


Shader::~Shader()
{
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value)const
{

}