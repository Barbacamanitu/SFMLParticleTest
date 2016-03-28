#include <Render\RenderMath.h>

RenderMath::RenderMath()
{
    //ctor
}

RenderMath::~RenderMath()
{
    //dtor
}

sf::Transform RenderMath::InterpolateTransforms(sf::Vector2f oldPosition, sf::Vector2f newPosition, float oldAngle, float newAngle, sf::Vector2f oldScale, sf::Vector2f newScale, float interpolation)
{

        sf::Vector2f interPos = oldPosition + ((newPosition - oldPosition) * interpolation);
        float interAngle = InterpolateAngles(oldAngle,newAngle,interpolation);
        sf::Vector2f interScale = oldScale + ((newScale - oldScale) * interpolation);

        sf::Transform value;
        value.translate(interPos);
        value.scale(interScale);
        value.rotate(interAngle);
        return value;

}

float RenderMath::InterpolateAngles(float oldAngle,float newAngle, float interpolation)
{
     float difference = std::abs(newAngle - oldAngle);
        if (difference > 180)
        {
            if (newAngle > oldAngle)
            {
                oldAngle += 360;
            }
            else
            {
                newAngle += 360;
            }
        }

        // Interpolate it.
        float value = (oldAngle + ((newAngle - oldAngle) * interpolation));

        // Wrap it..
        float rangeZero = 360;

        if (value >= 0 && value <= 360)
           return value;
        else
        return (int)(value) % 360;

}


