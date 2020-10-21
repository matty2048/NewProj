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
	const char* fcode = fstring.c_str();

	
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

	glShaderSource(fshader, 1, &fcode, NULL);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fshader, 512, NULL, infolog);
		std::cout << "frag shader error " << infolog << std::endl;
		return;
	}
	m_ShaderID = glCreateProgram();
	glAttachShader(m_ShaderID, vshader);
	glAttachShader(m_ShaderID, fshader);

	glLinkProgram(m_ShaderID);
	glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ShaderID, 512, NULL, infolog);
		std::cout << "Link error " << infolog << std::endl;
	}
	glDeleteShader(fshader);
	glDeleteShader(vshader);
}

void Shader::bind()
{
	glUseProgram(m_ShaderID);
}

void Shader::setmat4(const char* path, glm::mat4 mat)
{
	glUseProgram(m_ShaderID);
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderID,path), 1, GL_FALSE, &mat[0][0]);
	glUseProgram(0);

}
