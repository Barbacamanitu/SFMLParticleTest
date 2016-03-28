#pragma once
#include <SFML\Graphics.hpp>
class VectorMath
{
public:
	VectorMath();
	~VectorMath();
	static float Distance(const sf::Vector2f& first, const sf::Vector2f& second);
	static float Magnitude(const sf::Vector2f& vec);
	static bool DoesCircleContainPoint(sf::Vector2f center, float radius, sf::Vector2f point);
};

