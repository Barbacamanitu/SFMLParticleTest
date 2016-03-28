#include "stdafx.h"
#include "..\..\include\Particles\GLUtility.h"
#include <fstream>
#include <cstring>
#include <string>
#include <iostream>

GLUtility::GLUtility()
{

}


GLUtility::~GLUtility()
{
}

const GLchar* GLUtility::loadShaderFromFile(const char* filename)
{
	std::ifstream in(filename);
	std::string * contents = new std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	
	return (const GLchar *)contents->c_str();
}

void GLUtility::ClearGLState()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glUseProgram(0);
	glDisable(GL_TEXTURE_2D);
}

const GLuint GLUtility::createShaderFromFile(const char* filename)
{
	//Load the source code of the shader
	std::ifstream in(filename);
	std::string contents((std::istreambuf_iterator<char>(in)),std::istreambuf_iterator<char>());
	const GLchar* glSource = (const GLchar*) contents.c_str();
	if (contents.length() == 0)
	{
		throw "Shader was empty.";
	}
	//Determine type of shader
	GLenum shaderType;
	const char* extension = &filename[strlen(filename) - 2];
	if (std::strcmp(extension, "vs") == 0)
	{
		shaderType = GL_VERTEX_SHADER;
	}
	else if (std::strcmp(extension, "gs") == 0)
	{
		shaderType = GL_GEOMETRY_SHADER;
	}
	else if (std::strcmp(extension, "fs") == 0)
	{
		shaderType = GL_FRAGMENT_SHADER;
	}
	else if (std::strcmp(extension, "cm") == 0)
	{
		shaderType = GL_COMPUTE_SHADER;
	}

	//Create shader
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &glSource, NULL);
	glCompileShader(shader);
	

	//Check to make sure shader compiled properly
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{

		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		throw buffer;
	}

	return shader;
	

}

