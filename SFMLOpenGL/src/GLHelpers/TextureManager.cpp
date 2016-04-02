#include "stdafx.h"
#include "GLHelpers\TextureManager.h"
#include <utility>

namespace spl
{
	TextureManager* TextureManager::m_Manager = nullptr;
	TextureManager::TextureManager()
	{
	}
	
	
	TextureManager::~TextureManager()
	{
	}

	TextureManager& TextureManager::getInstance()
	{
		if (m_Manager == nullptr)
		{
			m_Manager = new TextureManager();
		}
		return *m_Manager;
	}

	spl::Texture TextureManager::loadTexture(std::string filename)
	{
		spl::Texture newTexture;
		newTexture.createFromFile(filename);
		return newTexture;
	}

	void TextureManager::addTexture(std::string textureName, std::string filename)
	{
		if (m_Textures.find(textureName) == m_Textures.end())
		{
			//Texture name isn't in the manager. Add it.
			spl::Texture newTexture = loadTexture(filename);
			m_Textures.insert(std::make_pair(textureName, newTexture));
		}
	}

	spl::Texture* TextureManager::lookupTexture(std::string name)
	{
		auto it = m_Textures.find(name);
		if (it != m_Textures.end())
		{
			return &it->second;
		}
		return nullptr;
	}

}
