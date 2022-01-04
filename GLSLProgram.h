#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);// read from file and compile for opengl to use

	void addAttribute(const std::string& attributeName);
	
	void linkShaders();

	void use();
	void unuse();

private:

	int _numAttributes;

	GLuint _programID;

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;

	void compileShader(const std::string& filePath, GLuint id);


};

