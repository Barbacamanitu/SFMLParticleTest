#include <Math\VectorMath.h>


VectorMath::VectorMath()
{
}


VectorMath::~VectorMath()
{
}

float VectorMath::Distance(const sf::Vector2f& first, const sf::Vector2f& second)
{
	return Magnitude(first - second);
}

float VectorMath::Magnitude(const sf::Vector2f& vec)
{
	return abs(sqrt(pow(vec.x, 2.0f) + pow(vec.y, 2.0f)));
}

bool VectorMath::DoesCircleContainPoint(sf::Vector2f center, float radius, sf::Vector2f point)
{
	return Distance(center, point) <= radius;
}
