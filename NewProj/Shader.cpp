#include "Shader.h"

Shader::Shader(const char* fragpath, const char* vertpath) 
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

	unsigned int vshader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fshader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vcode = vstring.c_str();
	const char* fcode = fstring.c_str(); //loads the shaders code

	
	int success;
	char infolog[512];
	glShaderSource(vshader, 1, &vcode , NULL); //adds the vertex shader code
	glCompileShader(vshader); //compiles the vertex shader
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &success); //checks errors
	if (!success)
	{
		glGetShaderInfoLog(vshader, 512, NULL, infolog);
		std::cout << "vertex shader error " << infolog << std::endl;
		return;
	}

	glShaderSource(fshader, 1, &fcode, NULL); //adds fragment shader code
	glCompileShader(fshader); //compiles fragment shader
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &success); //checks for errors
	if (!success)
	{
		glGetShaderInfoLog(fshader, 512, NULL, infolog);
		std::cout << "frag shader error " << infolog << std::endl;
		return;
	}
	m_ShaderID = glCreateProgram(); //creates the entire shader program
	glAttachShader(m_ShaderID, vshader); //attaches the vertex and fragment shaders
	glAttachShader(m_ShaderID, fshader);

	glLinkProgram(m_ShaderID); //links the two shaders
	glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);//checks for errors
	if (!success)
	{
		glGetProgramInfoLog(m_ShaderID, 512, NULL, infolog);
		std::cout << "Link error " << infolog << std::endl;
	}
	glDeleteShader(fshader); //cleans up
	glDeleteShader(vshader);
}

void Shader::Bind()
{
	glUseProgram(m_ShaderID);
}

void Shader::SetMat4(const char* path, glm::mat4 mat)
{
	glUseProgram(m_ShaderID);
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderID,path), 1, GL_FALSE, &mat[0][0]);
	glUseProgram(0);

}

void Shader::SetBool(const char* path, bool mat)
{
	glUseProgram(m_ShaderID);
	glUniform1i(glGetUniformLocation(m_ShaderID, path), mat);
	glUseProgram(0);

}

void Shader::SetInt(const char* path, int i)
{
	glUseProgram(m_ShaderID);
	glUniform1i(glGetUniformLocation(m_ShaderID, path), i);
	glUseProgram(0);
}
