#version 410 core

in vec3 normal;
out vec4 FragColor;

vec3 light_dir = vec3(1.f, 0.f, 0.f);

void main()
{
  float light = dot(light_dir, normal);
  FragColor = vec4(light, light, light, 1.f);
} 