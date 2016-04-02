#pragma once
#include "GL/glew.h"
#include "Shader.h"
#include <vector>
#include <map>
namespace spl
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

			
		enum ProgramType
		{
			//Two main types of shader programs to simulate particles.
			Compute,
			Render
		};
		

		GLuint Id() const { return id; }
		void attachShader(Shader shader);
		void link();
		void addAttribute(std::string name);
		void addUniform(std::string name);
		void makeActive();
		//Factory methods
		static ShaderProgram CreateComputeProgram();
		static ShaderProgram CreateRenderProgram();

		//Set 
	private:
		GLuint id;
		std::vector<Shader> shaders;

		//This map stores all of the attribute names, types, and locations
		//This includes uniforms
		std::map<std::string, GLuint> attributeLocations;
		std::map<std::string, GLuint> uniformLocations;
		
	};
}

