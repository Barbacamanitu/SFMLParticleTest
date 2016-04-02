#pragma once
#include "glm/glm.hpp"
namespace spl
{

	//Convenience object to simplify making openGL ModelViewProjection matrix
	class MVPMatrix
	{
	public:
		MVPMatrix();
		~MVPMatrix();

		glm::mat4 MvpMatrix() const;
		glm::mat4 ModelMatrix() const { return modelMatrix; }
		glm::mat4 ViewMatrix() const { return viewMatrix; }
		glm::mat4 ProjectionMatrix() const { return projectionMatrix; }



		//Model
		void move(float x, float y);
		void rotate(float degrees);
		
		//View
		void setCameraPosition(float x, float y, float z, float depth);

		//Projection
		void setOrthographicProjection(float windowWidth, float windowHeight, float nearClip, float farClip);
	private:
		glm::mat4 mvpMatrix;
		glm::mat4 modelMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;
	};
}
