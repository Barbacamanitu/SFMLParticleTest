#ifndef RENDERMATH_H
#define RENDERMATH_H
#include <SFML/Graphics.hpp>

class RenderMath
{
    public:
        RenderMath();
        virtual ~RenderMath();
        static sf::Transform InterpolateTransforms(sf::Vector2f oldPosition, sf::Vector2f newPosition, float oldAngle, float newAngle, sf::Vector2f oldScale, sf::Vector2f newScale, float interpolation);
        static float InterpolateAngles(float oldAngle,float newAngle, float interpolation);
    protected:
    private:
};

#endif // RENDERMATH_H
