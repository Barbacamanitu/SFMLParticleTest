#include "stdafx.h"
#include "GLHelpers\ShaderProgram.h"
#include "ErrorHandling\SPLException.h"

namespace spl
{

	ShaderProgram::ShaderProgram()
	{
		id = glCreateProgram();
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
	}

	
	


	ShaderProgram ShaderProgram::CreateComputeProgram()
	{
		Shader computeShader;
		computeShader.compileFromFile("shaders\\move.cs");
		ShaderProgram computeProgram;
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
		renderProgram.attachShader(renderVertexShader);
		renderProgram.attachShader(renderGeoShader);
		renderProgram.attachShader(renderFragmentShader);
		renderProgram.link();
		return renderProgram;
	}

	void ShaderProgram::addAttribute(std::string name)
	{
		//Program must be active!		
		attributeLocations.insert(std::make_pair(name, glGetAttribLocation(id, name.c_str())));
	}

	void ShaderProgram::addUniform(std::string name)
	{		
		//Program must be active!
		uniformLocations.insert(std::make_pair(name, glGetUniformLocation(id, name.c_str())));
	}

	void ShaderProgram::makeActive()
	{
		glUseProgram(id);
	}

}