#include "stdafx.h"
#include "GLHelpers\MVPMatrix.h"
#include "glm\gtc\matrix_transform.hpp"

namespace spl
{
	MVPMatrix::MVPMatrix()
	{
		
	}


	MVPMatrix::~MVPMatrix()
	{
	}

	glm::mat4 MVPMatrix::MvpMatrix() const
	{
		return  projectionMatrix * viewMatrix * modelMatrix;
	}

	void MVPMatrix::setOrthographicProjection(float windowWidth, float windowHeight, float nearClip, float farClip)
	{
		float windowLeft = windowWidth - (windowWidth * .5f);
		float windowRight = windowWidth + (windowWidth * .5f);
		float windowTop = windowHeight + (windowHeight * .5f);
		float windowBottom = windowHeight - (windowHeight * .5f);
		projectionMatrix = glm::ortho(windowLeft,windowRight,windowBottom,windowTop, nearClip, farClip);
	}

	void MVPMatrix::setCameraPosition(float x, float y, float z, float depth)
	{
		viewMatrix = glm::lookAt(
			glm::vec3(x, y, z),
			glm::vec3(x, y, z + depth),
			glm::vec3(0.0f, 1.0f, 0.0f));
	}

	void MVPMatrix::rotate(float degrees)
	{
		//Not implemented
	}

	void MVPMatrix::move(float x, float y)
	{
		//Not implemented
	}

}
