#include "Shader.h"

Shader::Shader(const char* fragpath, const char* vertpath) //shader constructor
{
	std::ifstream fragfile;
	fragfile.open(fragpath);
	std::stringstream fsstream;
	fsstream << fragfile.rdbuf();
	std::string fstring = fsstream.str(); 

	std::ifstream vertfile;
	vertfile.open(vertpath);
	std::stringstream vsstream;
	vsstream << vertfile.rdbuf();
	std::string vstring = vsstream.str();
					
	// ^^ copies contents of shader files to c++  strings

	unsigned int vshader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fshader = glCreateShader(GL_FRAGMENT_SHADER);
	//creates the shader programs


	const char* vcode = vstring.c_str();
	const char* fcode = fstring.c_str();
	//converts the C++ style strings containing shaders to c arrays
	
	int success;
	char infolog[512];
	glShaderSource(vshader, 1, &vcode , NULL);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vshader, 512, NULL, infolog);
		std::cout << "vertex shader error " << infolog << std::endl;
		return;
	}
	//compiles the vertex  shader

	glShaderSource(fshader, 1, &fcode, NULL);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fshader, 512, NULL, infolog);
		std::cout << "frag shader error " << infolog << std::endl;
		return;
	}
	//compiles the fragment shader
	m_ShaderID = glCreateProgram();
	glAttachShader(m_ShaderID, vshader);
	glAttachShader(m_ShaderID, fshader);
	//creates the combined shader program and adds the vertex and fragement shaders 

	glLinkProgram(m_ShaderID);
	glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ShaderID, 512, NULL, infolog);
		std::cout << "Link error " << infolog << std::endl;
	}
	//links the combined shader program
	glDeleteShader(fshader);
	glDeleteShader(vshader);
	//deletes the two now unused sub shaders
}

void Shader::Bind() //binds the shader program for use
{
	glUseProgram(m_ShaderID); 
}

void Shader::SetMat4(const char* path, glm::mat4 mat) //passes a mat4 uniform to shader (16-bytes)
{
	glUseProgram(m_ShaderID);
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderID,path), 1, GL_FALSE, &mat[0][0]);
	glUseProgram(0);

}
