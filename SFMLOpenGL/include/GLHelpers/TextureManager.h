#pragma once
#include "GL/glew.h"
#include <map>
#include <string>
#include "Texture.h"
namespace spl
{
	class TextureManager
	{
	public:
		static TextureManager& getInstance();
		TextureManager();
		~TextureManager();


		//Texture loading methods
		void addTexture(std::string textureName, std::string filename);
		spl::Texture* lookupTexture(std::string name);
	private:
		spl::Texture loadTexture(std::string filename);

		static TextureManager *m_Manager;
		std::map<std::string, spl::Texture> m_Textures;
	};
}

