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
		GLuint ID() const { return id; }


		GLint loadFromFile(const char* filename);
		GLint loadFromFile(const char* filename, ShaderType type);
		void compileFromFile(const char* filename);
		void compile();

		

	private:
		ShaderType m_Type;
		GLuint id;
		

		ShaderType findShaderType(const char* filename);
		GLuint createShader(const GLchar* source);
	};
}

