#version 430
layout (local_size_x = 512, local_size_y = 1, local_size_z = 1) in;

#define C_GRAVITY 5000.0
#define MAX_SPEED 100.0
#define MIN_DISTANCE 20.0

layout (std430, binding = 0) buffer PositionBuffer {
vec4 Particle[]; 
};

uniform float deltaTime;
uniform vec2 mousePos;
uniform float mouseForce;


vec2 calculateAcceleration(vec2 particlePosition)
{

	float distance = pow(distance(mousePos,particlePosition),.5);
	
	
	float force = C_GRAVITY / (distance);
	vec2 accelDirection = normalize(mousePos - particlePosition);
	return accelDirection * force * mouseForce;
	
}

 vec2 rotatePoint(vec2 point, float angle){
		   angle = radians(angle);
           vec2 rotated_point;
           rotated_point.x = point.x * cos(angle) - point.y * sin(angle);
           rotated_point.y = point.x * sin(angle) + point.y * cos(angle);
           return rotated_point;
   }
   



void main()
{
	vec2 indexv = gl_GlobalInvocationID.xy;
	uint index = uint((indexv.x * 10) + indexv.y);
	
	vec2 currentVelocity = Particle[index].zw;
	vec2 currentPosition = Particle[index].xy;
	
	float step = 0.01;
	
	
	float x = currentPosition.x;
	float y = currentPosition.y;
	
	vec2 otherPosition = currentPosition + vec2(step,step);
	float xx = otherPosition.x;
	float yy = otherPosition.y;
	
	
	vec2 vecFieldA = vec2(y,-x);
	vec2 vecFieldB = vec2(yy,-xx);
	float curl = (vecFieldB.y - vecFieldA.y) / (vecFieldB.x - vecFieldA.x);
	curl *= 45.0;
	
	
	
	
	vec2 acceleration = vec2(0.0,0.0) + calculateAcceleration(currentPosition);
	vec2 newVelocity = currentVelocity + (acceleration * deltaTime);
	//newVelocity = vecFieldB;

	newVelocity = vec2(0.0,150.0);
	newVelocity = rotatePoint(newVelocity,curl);
	
	
	
	//Apply position update
	Particle[index].xy = currentPosition + newVelocity * deltaTime;	
	Particle[index].zw = newVelocity * .99;
	
	
}