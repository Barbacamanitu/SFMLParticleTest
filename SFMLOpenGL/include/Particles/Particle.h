#include "glm/glm.hpp"
namespace spl
{
#pragma pack(push, 1)
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
	};
#pragma pack(pop)
}