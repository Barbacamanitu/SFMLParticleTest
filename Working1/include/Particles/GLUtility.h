#pragma once
#include <gl\glew.h>
class GLUtility
{
public:
	GLUtility();
	~GLUtility();
	static const GLchar * loadShaderFromFile(const char* filename);
	static const GLuint createShaderFromFile(const char* filename);
	static void ClearGLState();
};

