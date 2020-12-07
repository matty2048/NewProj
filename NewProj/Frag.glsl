#version 330 core
layout(location = 0)out vec4 colour;
in vec3 Normal;
in vec3 FragPos;

void main()
{
	vec3 ambient = vec3(0.1,0.1,0.1);
	vec3 lightPos = vec3(0,3,-5);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(0.5,0.6,0.6);
	vec3 result = (diffuse + ambient) * vec3(0.1,0.5,1.0);
	colour = vec4(result,1.0);
}