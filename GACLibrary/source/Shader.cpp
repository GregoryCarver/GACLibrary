#include "../header/Shader.h"

/*******************************************************************************************************************************************************
* Shader class that contains the shader program ID, and functions to use the program and update uniforms
* 
* Function descriptions (that I need):
*		- glShaderSource(specific shader ID(unsigned int), 
*						 count(unsigned int), 
*						 single or array of shader codes(const char* or char**), 
*						 array of lengths associated with the array of shader codes(unsigned int or NULL))
*		- glGetShaderiv(specific shader ID(unsigned int),
*						object parameter(GLenum: GL_SHADER_TYPE, GL_DELETE_STATUS, GL_COMPILE_STATUS, GL_INFO_LOG_LENGTH, GL_SHADER_SOURCE_LENGTH),
*						returned object parameters like if successful or not(unsigned int)
*		- glGetShaderInfoLog(specific shader ID(unsigned int),
*							 character buffer size that info is returned to(unsigned int),
*							 returns length of the string returned in infoLog(unsigned int or NULL),
*							 character array to store infoLog(char*)
*
* Steps to create shader in constructor:
*		Step 1: Parse shader source code from file
*		Step 2:	Compile specific shaders
*			- glCreateShader
*			- glShaderSource
*			- glCompileShader
*			- glGetShaderiv
*			- glGetShaderInfoLog
*		Step 3: Compile shader program
*			- glCreateProgram
*			- glAttachShader
*			- glLinkProgram
*			- glGetProgramiv
*			- glGetProgramInfoLog
*		Step 4: Delete the specific shaders
*			- glDeleteShader
*******************************************************************************************************************************************************/
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	/*** Step 1: Retrieve shaders source code ***/
	std::string vShaderCode;
	std::string fShaderCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//Ensure ifstream can throw exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vShaderCode = vShaderStream.str();
		fShaderCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_READ_SUCCESSFULLY" << std::endl;
	}

	const char* vertexCode = vShaderCode.c_str();
	const char* fragmentCode = fShaderCode.c_str();

	/*** Step 2: Compile the shaders ***/
	unsigned int vertexShader, fragmentShader;
	int success;
	char infoLog[512];

	//Compile vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	glCompileShader(vertexShader);
	//Print compile errors if any
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Compile fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	glCompileShader(fragmentShader);
	//Print compile errors if any
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/*** Step 3: Compile the shader program ***/
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	//Print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	/*** Step 4: Delete the shaders that have been linked ***/
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

//void Shader::SetMat4(const std::string& name, glm::mat4* value) const
//{
//	/*std::cout << name << ":  " << std::endl;
//	std::cout << (*value)[0][0] << std::endl;*/
//	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &(*value)[0][0]);
//}

unsigned int Shader::GetID()
{
	return ID;
}
