#include "stdafx.h"
#include "GLHelpers\Shader.h"
#include <string>
#include <fstream>
#include "GL\glew.h"
#include "ErrorHandling\ShaderException.h"
namespace spl
{

	Shader::Shader()
	{
	}


	Shader::~Shader()
	{
	}

	GLint Shader::loadFromFile(const char* filename)
	{
		ShaderType type = findShaderType(filename);
		return loadFromFile(filename, type);
	}

	GLint Shader::loadFromFile(const char* filename, ShaderType type)
	{
		m_Type = type;

		//Load source code contents
		std::ifstream in(filename);
		if (!in.good())
		{
			throw spl::ShaderException(spl::ShaderErrorIDs::FileNotFound);
			in.close();
		}
		std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		if (contents.length() == 0)
		{
			throw spl::ShaderException(spl::ShaderErrorIDs::EmptySourceFile);
		}
		const GLchar* glSource = (const GLchar*)contents.c_str();
		GLuint shaderID = createShader(glSource);
		return shaderID;
	}

	ShaderType Shader::findShaderType(const char* filename)
	{
		//Get the extension of the file
		std::string filenameString(filename);

		size_t lastDot = filenameString.find_last_of(".");
		if (lastDot == std::string::npos || lastDot == filenameString.length()-1)
		{
			throw spl::ShaderException(spl::ShaderErrorIDs::FileNotFound);
		}

		std::string extension = filenameString.substr(lastDot+1);
		

		if (extension.compare("vs") == 0)
		{
			return ShaderType::Vertex;
		}
		if (extension.compare("fs") == 0)
		{
			return ShaderType::Fragment;
		}
		if (extension.compare("gs") == 0)
		{
			return ShaderType::Geometry;
		}
		if (extension.compare("cs") == 0)
		{
			return ShaderType::Compute;
		}
		//If code makes it here, the exntension isn't supported.
		throw spl::ShaderException(spl::ShaderErrorIDs::UnsupportedFormat);
	}

	GLuint Shader::createShader(const GLchar* source)
	{
		GLuint shaderType;
		switch (m_Type)
		{
		case ShaderType::Compute:
			shaderType = GL_COMPUTE_SHADER;
			break;
		case ShaderType::Fragment:
			shaderType = GL_FRAGMENT_SHADER;
			break;
		case ShaderType::Geometry:
			shaderType = GL_FRAGMENT_SHADER;
			break;
		case ShaderType::Vertex:
			shaderType = GL_VERTEX_SHADER;
			break;

		}
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &source, NULL);
		return shader;
	}

}
