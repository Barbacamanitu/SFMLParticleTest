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
uniform vec4 obstacles[];

// Helper constants
#define F2 0.366025403
#define G2 0.211324865
#define K 0.0243902439 // 1/41

// Permutation polynomial
float permute(float x) {
  return mod((34.0 * x + 1.0)*x, 289.0);
}

// Gradient mapping with an extra rotation.
vec2 grad2(vec2 p, float rot) {
#if 1
// Map from a line to a diamond such that a shift maps to a rotation.
  float u = permute(permute(p.x) + p.y) * K + rot; // Rotate by shift
  u = 4.0 * fract(u) - 2.0;
  return vec2(abs(u)-1.0, abs(abs(u+1.0)-2.0)-1.0);
#else
#define TWOPI 6.28318530718
// For more isotropic gradients, sin/cos can be used instead.
  float u = permute(permute(p.x) + p.y) * K + rot; // Rotate by shift
  u = fract(u) * TWOPI;
  return vec2(cos(u), sin(u));
#endif
}

float srdnoise(in vec2 P, in float rot, out vec2 grad) {

  // Transform input point to the skewed simplex grid
  vec2 Ps = P + dot(P, vec2(F2));

  // Round down to simplex origin
  vec2 Pi = floor(Ps);

  // Transform simplex origin back to (x,y) system
  vec2 P0 = Pi - dot(Pi, vec2(G2));

  // Find (x,y) offsets from simplex origin to first corner
  vec2 v0 = P - P0;

  // Pick (+x, +y) or (+y, +x) increment sequence
  vec2 i1 = (v0.x > v0.y) ? vec2(1.0, 0.0) : vec2 (0.0, 1.0);

  // Determine the offsets for the other two corners
  vec2 v1 = v0 - i1 + G2;
  vec2 v2 = v0 - 1.0 + 2.0 * G2;

  // Wrap coordinates at 289 to avoid float precision problems
  Pi = mod(Pi, 289.0);

  // Calculate the circularly symmetric part of each noise wiggle
  vec3 t = max(0.5 - vec3(dot(v0,v0), dot(v1,v1), dot(v2,v2)), 0.0);
  vec3 t2 = t*t;
  vec3 t4 = t2*t2;

  // Calculate the gradients for the three corners
  vec2 g0 = grad2(Pi, rot);
  vec2 g1 = grad2(Pi + i1, rot);
  vec2 g2 = grad2(Pi + 1.0, rot);

  // Compute noise contributions from each corner
  vec3 gv = vec3(dot(g0,v0), dot(g1,v1), dot(g2,v2)); // ramp: g dot v
  vec3 n = t4 * gv;  // Circular kernel times linear ramp

  // Compute partial derivatives in x and y
  vec3 temp = t2 * t * gv;
  vec3 gradx = temp * vec3(v0.x, v1.x, v2.x);
  vec3 grady = temp * vec3(v0.y, v1.y, v2.y);
  grad.x = -8.0 * (gradx.x + gradx.y + gradx.z);
  grad.y = -8.0 * (grady.x + grady.y + grady.z);
  grad.x += dot(t4, vec3(g0.x, g1.x, g2.x));
  grad.y += dot(t4, vec3(g0.y, g1.y, g2.y));
  grad *= 40.0;

  // Add contributions from the three corners and return
  return 40.0 * (n.x + n.y + n.z);
}

vec2 calculateAcceleration(vec2 particlePosition)
{

	float distanceA = pow(distance(mousePos,particlePosition),.5);
	
	float force = C_GRAVITY / (distanceA);
	vec2 accelDirection = normalize(mousePos - particlePosition);
	
	accelDirection = accelDirection * force * mouseForce;
	
	return accelDirection;
	
}

void main()
{
	vec2 indexv = gl_GlobalInvocationID.xy;
	uint index = uint((indexv.x * 10) + indexv.y);
	
	vec2 currentVelocity = Particle[index].zw;
	vec2 currentPosition = Particle[index].xy;
	vec2 accel = calculateAcceleration(currentPosition) * .5;
	

	
	vec2 grad;
	float screenWidth = 200.0;
	vec2 adjustedPos = currentPosition / screenWidth;
	
	float n1 = srdnoise(adjustedPos, 90, grad);
	float curl = grad.y - grad.x;
	curl*= 2;
	vec2 turnVec = vec2(grad.y,-grad.x) * deltaTime * min(length(currentVelocity),10.0) ;
	accel.y += max(50.0,abs(turnVec.y));
	currentVelocity += accel * deltaTime;
	currentVelocity += turnVec;
		
	vec2 nextPosition = currentPosition + currentVelocity * deltaTime;
	float obstacleSize = 30;
	vec2 obstacle = obstacles[0].xy;
	vec2 obstacleOld = obstacles[0].zw;
	vec2 obstacleVelocity = obstacle - obstacleOld;
	
	float distanceA = distance(currentPosition,obstacle);
	float distanceB = distance(nextPosition,obstacle);
	if (distanceB <= obstacleSize)
	{
		vec2 normal = normalize(nextPosition-obstacle);
		//Do projection
		float penDistance = obstacleSize - distanceB;
		currentPosition += normal * (penDistance);
		
		//Bound
		currentVelocity = reflect(currentVelocity,normal) * .7;
		//currentVelocity -= (currentPosition - obstacleOld) * .5;
	}
		
		
	
		
		
	currentPosition += currentVelocity * deltaTime;
	
	
	
	Particle[index].xy = currentPosition;
	Particle[index].zw = currentVelocity * .99;
	
	
}