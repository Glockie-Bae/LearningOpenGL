#pragma once

#include<glad\glad.h>
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include"ShaderSource.h"
#include"glm\glm.hpp"
#include"glm\gtc\matrix_transform.hpp"
#include"glm\gtc\type_ptr.hpp"


class Shader {
private:
	const std::string m_shader_file_path;
	std::string m_vertex_shader_source;
	std::string m_fragement_shader_source;
	unsigned int m_program;

public:
	Shader(const std::string shaderfile) 
	: m_shader_file_path(shaderfile){

	}
	void CompileShader();
	unsigned int CreateShader(unsigned int type, const std::string& source);
	void ParseShader();
	void UseProgram();
	void BindTexture(unsigned int type, unsigned int texture_id);
	int GetUniformLoaction(const char* name);
	void SetInt(const char * name, const int value);
	void SetMat4f(const char* name, const glm::mat4 matrix);
	void SetFloat(const char* name, const float value);
};