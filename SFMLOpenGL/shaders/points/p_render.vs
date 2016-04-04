#version 430
#define MAX_SPEED 500.0

in vec2 velocity;
in vec2 position;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
out vec4 vertexColor;


void main()
{
	vec4 blue =  vec4(0,.5,1,.5);
	vec4 green = vec4(0,1,.25,.5);
	gl_Position =  projectionMatrix * modelViewMatrix * vec4(position, 0.0, 1.0);
	float speed = length(velocity) / 200.0;
	vertexColor = mix(blue,green,speed);
	
}

