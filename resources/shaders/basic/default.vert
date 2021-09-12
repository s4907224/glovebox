#version 410 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

uniform mat4 MVP;

out vec3 normal;
out vec3 frag_pos;

void main()
{
  vec4 position = MVP * vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.f);
  gl_Position = position;
  normal = vertex_normal;
  frag_pos = position.xyz;
}