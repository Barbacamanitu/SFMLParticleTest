#include "stdafx.h"
#include "GLHelpers\ShaderProgram.h"
#include "ErrorHandling\SPLException.h"

namespace spl
{

	ShaderProgram::ShaderProgram()
	{
		id = 0;
	}


	ShaderProgram::~ShaderProgram()
	{
	}

	void ShaderProgram::attachShader(Shader shader)
	{
		shaders.push_back(shader);
		glAttachShader(id, shaders.back().ID());
	}

	void ShaderProgram::link()
	{
		glLinkProgram(id);
		GLint status;
		glGetProgramiv(id, GL_LINK_STATUS, &status);

		if (status != GL_TRUE)
		{
			char buffer[512];
			glGetProgramInfoLog(id, 512, NULL, buffer);
			int a = 1;
		}
	}

	
	


	ShaderProgram ShaderProgram::CreateComputeProgram()
	{
		Shader computeShader;
		computeShader.compileFromFile("shaders\\curl.cs");
		ShaderProgram computeProgram;
		computeProgram.CreateProgram();
		computeProgram.attachShader(computeShader);
		computeProgram.link();
		return computeProgram;
	}



	ShaderProgram ShaderProgram::CreateRenderProgram()
	{
		Shader renderVertexShader, renderGeoShader, renderFragmentShader;
		renderVertexShader.compileFromFile("shaders\\render.vs");
		renderGeoShader.compileFromFile("shaders\\render.gs");
		renderFragmentShader.compileFromFile("shaders\\render.fs");

		ShaderProgram renderProgram;
		renderProgram.CreateProgram();
		renderProgram.attachShader(renderVertexShader);
		renderProgram.attachShader(renderGeoShader);
		renderProgram.attachShader(renderFragmentShader);
		renderProgram.link();
		return renderProgram;
	}

	std::map<std::string, ShaderProgram::VertexAttribute>& ShaderProgram::getAttributes()
	{
		return attributeLocations;
	}

	void ShaderProgram::addAttribute(std::string name, size_t offset, size_t size, size_t componentCount)
	{
		//Program must be active!		
		makeActive();

		VertexAttribute attr;
		attr.Location = glGetAttribLocation(id, name.c_str());
		attr.Offset = offset;
		attr.Size = size;
		attr.ComponentCount = componentCount;

		attributeLocations.insert(std::make_pair(name, attr));
	}


	void ShaderProgram::addUniform(std::string name)
	{		
		//Program must be active!
		makeActive();
		uniformLocations.insert(std::make_pair(name, glGetUniformLocation(id, name.c_str())));
	}

	void ShaderProgram::makeActive()
	{
		GLint err = glGetError();
		glUseProgram(id);
		err = glGetError();
	}

	void ShaderProgram::CreateProgram()
	{
		id = glCreateProgram();

	}

	spl::ShaderProgram ShaderProgram::CreateRenderProgramPoints()
	{
		Shader renderVertexShader, renderGeoShader, renderFragmentShader;
		renderVertexShader.compileFromFile("shaders\\points\\render.vs");
		renderGeoShader.compileFromFile("shaders\\render.gs");
		renderFragmentShader.compileFromFile("shaders\\points\\render.fs");

		ShaderProgram renderProgram;
		renderProgram.CreateProgram();
		renderProgram.attachShader(renderVertexShader);
		//renderProgram.attachShader(renderGeoShader);
		renderProgram.attachShader(renderFragmentShader);
		renderProgram.link();
		return renderProgram;
	}

}