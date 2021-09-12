#version 410 core
layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

out vec3 normal;
out vec3 frag_pos;

void main()
{
  gl_Position = vec4(vertex_position.x, vertex_position.y, vertex_position.z, 1.0);
  normal = vertex_normal;
  frag_pos = gl_Position.xyz;
}