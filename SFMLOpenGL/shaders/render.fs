#version 430

uniform sampler2D tex0;
in vec2 Vertex_UV;
in vec4 Vertex_Color;
out vec4 outColor;

void main()
{
  vec2 uv = Vertex_UV.xy;
  uv.y = 1 - uv.y;
  vec4 t = texture(tex0,uv).rgba;
  outColor = t * Vertex_Color;
}