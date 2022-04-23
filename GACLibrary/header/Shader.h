#pragma once

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//Shader class that contains the shader program ID, and functions to use the program and update uniforms. Class description in cpp file
class Shader
{
private:
	//ID for the shader program
	unsigned int ID;

public:
	Shader(const char* vertexPath, const char* fragmentPath);

	void Use();

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	/*void SetMat4(const std::string& name, glm::mat4* value) const;*/

	unsigned int GetID();
};