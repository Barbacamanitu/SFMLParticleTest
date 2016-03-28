#pragma once
#include "GL/glew.h"
namespace spl
{
	enum ShaderType
	{
		Vertex, Geometry, Fragment, Compute
	};
	class Shader
	{
		

	public:
		Shader();
		~Shader();

		//Property Getters
		ShaderType GetType() const { return m_Type; }



		GLint loadFromFile(const char* filename);
		GLint loadFromFile(const char* filename, ShaderType type);

		

	private:
		ShaderType m_Type;
		
		ShaderType findShaderType(const char* filename);
		GLuint createShader(const GLchar* source);
	};
}

