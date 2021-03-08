#version 330 core
layout(location = 0)out vec4 colour;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform bool HasTex;

uniform sampler2D Diffuse1;
uniform sampler2D Diffuse2;
uniform sampler2D Diffuse3;

uniform sampler2D Spec1;
uniform sampler2D Spec2;
uniform sampler2D Spec3;
void main()
{
	vec3 ambient = normalize(vec3(0.1,0.1,0.1));
	vec3 lightPos = vec3 (0,0,-5);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);  
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(0.1,0.1,0.1);
	vec3 result = (diffuse + ambient) * (HasTex ? texture2D(Diffuse1,TexCoord).rgb : vec3(0.1,0.5,0.5)); 
	colour = vec4(result,1.0);
}