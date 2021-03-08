#version 330 core 
//Compiler hint for the opengl version^


layout (location = 0) in vec3 aPos; //takes in the position of the verticies in the mesh
layout (location = 1) in vec3 aNorm; //takes in the normal vectors
layout (location = 2) in vec2 TexCord; //takes in the coordinates of textures on the mesh
uniform mat4 projection; //the perspective projection matrix 
uniform mat4 view;		 //the matrix from the camera 
uniform mat4 model;		 //the transformation of the model
out vec3 Normal;		 //outputs the normal for the fragment shader
out vec3 FragPos;		 //outputs the postion of the fragments in world space
out vec2 TexCoord;		 //outputs and interpolated texture coordinate for the fragment
void main()
{
	
	gl_Position = projection * view * model * vec4(aPos,1.0f); //puts the mesh into screen space
	FragPos = vec3(model*vec4(aPos,1.0f));					   //the fragments position in world space
	TexCoord = TexCord;						//sets the texture coordinates
	Normal = aNorm;							//sets the normal vectors
}