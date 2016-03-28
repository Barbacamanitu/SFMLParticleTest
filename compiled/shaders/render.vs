#version 430
#define MAX_SPEED 500.0


in vec2 position;
in vec2 velocity;
uniform mat4 modelViewMatrix;
out vec4 vertexColor;


void main()
{
	vec4 slow = vec4(0.2,0.2,.85,.5);
	vec4 fast = vec4(0.2,0.85,.2,.5);
	gl_Position =  modelViewMatrix * vec4(position, 0.0, 1.0);
	float speed = length(velocity);
	speed = min(speed,MAX_SPEED);
	//Normalize speed
	speed = (speed / MAX_SPEED );
	vertexColor = mix(slow,fast,speed);

	
}

