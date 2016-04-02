#version 430
layout (local_size_x = 512, local_size_y = 1, local_size_z = 1) in;

#define C_GRAVITY 5000.0
#define MAX_SPEED 100.0
#define MIN_DISTANCE 20.0

layout (std430, binding = 0) buffer PositionBuffer {
vec4 Particle[]; 
vec4 Extra[]; 
};

uniform float deltaTime;
uniform vec2 mousePos;


vec2 calculateAcceleration(vec2 particlePosition)
{

	float distance = pow(distance(mousePos,particlePosition),.5);
	
	
	
	float force = C_GRAVITY / (distance);
	vec2 accelDirection = normalize(mousePos - particlePosition);
	return accelDirection * force;
	
}






void main()
{
	vec2 indexv = gl_GlobalInvocationID.xy;
	uint index = uint((indexv.x * 10) + indexv.y);
	
	vec2 currentVelocity = Particle[index].zw;
	vec2 currentPosition = Particle[index].xy;
	
	vec2 acceleration = calculateAcceleration(currentPosition);
	vec2 newVelocity = currentVelocity + (acceleration * deltaTime);
	
	//Apply position update
	Particle[index].xy = currentPosition + currentVelocity * deltaTime;	
	//Save velocity for next frame
	Particle[index].zw = newVelocity * 0.99;
	
	
}

