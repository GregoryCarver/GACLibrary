#pragma once

#include <glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//Class description in cpp file
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
};