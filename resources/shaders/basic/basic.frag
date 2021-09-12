#version 410 core

in vec3 normal;
in vec3 frag_pos;

out vec4 frag_colour;

void main()
{
  vec3 light_pos = vec3(3.f, 4.f, 2.f);

  vec3 light_colour = vec3(0.8f, 0.1f, 0.05f);
  vec3 object_colour = vec3(1.f, 1.f, 1.f);
  // ambient
  float ambient_strength = 0.2;
  vec3 ambient = ambient_strength * light_colour;    
  
    // diffuse 
  vec3 norm = normalize(normal);
  vec3 light_dir = normalize(light_pos - frag_pos);
  float diff = max(dot(norm, light_dir), 0.0);
  vec3 diffuse = diff * light_colour;
  
  // specular
  float specular_strength = 1.0;
  vec3 view_dir = normalize(-frag_pos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
  vec3 reflect_dir = reflect(-light_dir, norm);  
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
  vec3 specular = specular_strength * spec * light_colour; 
  
  vec3 result = (ambient + diffuse + specular) * object_colour;
  frag_colour = vec4(result, 1.0);
}