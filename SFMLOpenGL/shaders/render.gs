#version 430

layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 4) out;    
   
//Matrices
uniform mat4 projectionMatrix;

in vec4 vertexColor[];
uniform float particleSize;
 
out vec2 Vertex_UV;
out vec4 Vertex_Color;
   
void main (void)
{
  vec4 P = gl_in[0].gl_Position;
 
  // a: left-bottom 
  vec2 va = P.xy + vec2(-0.5, -0.5) * particleSize;
  gl_Position = projectionMatrix * vec4(va, P.zw);
  Vertex_UV = vec2(0.0, 0.0);
  Vertex_Color = vertexColor[0];
  EmitVertex();  
  
  // b: left-top
  vec2 vb = P.xy + vec2(-0.5, 0.5) * particleSize;
  gl_Position = projectionMatrix * vec4(vb, P.zw);
  Vertex_UV = vec2(0.0, 1.0);
  Vertex_Color = vertexColor[0];
  EmitVertex();  
  
  // d: right-bottom
  vec2 vd = P.xy + vec2(0.5, -0.5) * particleSize;
  gl_Position = projectionMatrix * vec4(vd, P.zw);
  Vertex_UV = vec2(1.0, 0.0);
  Vertex_Color = vertexColor[0];
  EmitVertex();  
 
  // c: right-top
  vec2 vc = P.xy + vec2(0.5, 0.5) * particleSize;
  gl_Position =  projectionMatrix * vec4(vc, P.zw);
  Vertex_UV = vec2(1.0, 1.0);
  Vertex_Color = vertexColor[0];
  EmitVertex();  
 
  EndPrimitive();  
}   