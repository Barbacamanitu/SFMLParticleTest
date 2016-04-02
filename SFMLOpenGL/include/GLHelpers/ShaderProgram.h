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
		struct VertexAttribute
		{
			GLuint Location;
			size_t Offset;
			size_t Size;
			size_t ComponentCount;
		};
			
		enum ProgramType
		{
			//Two main types of shader programs to simulate particles.
			Compute,
			Render
		};
		
		void CreateProgram();
		GLuint Id() const { return id; }
		void attachShader(Shader shader);
		void link();
		void addAttribute(std::string name, size_t offset, size_t size, size_t componentCount);
		void addUniform(std::string name);
		void makeActive();
		std::map<std::string, VertexAttribute>& getAttributes();
		//Factory methods
		static ShaderProgram CreateComputeProgram();
		static ShaderProgram CreateRenderProgram();
		static ShaderProgram CreateRenderProgramPoints();

		//Set 
	private:
		GLuint id;
		std::vector<Shader> shaders;

		//This map stores all of the attribute names, types, and locations
		//This includes uniforms
		std::map<std::string, VertexAttribute> attributeLocations;
		std::map<std::string, GLuint> uniformLocations;
		
	};
}

