#include"Shader.h"

void Shader::CompileShader(){
	this->m_program = glCreateProgram();
	unsigned int vertexshader = Shader::CreateShader(GL_VERTEX_SHADER, this->m_vertex_shader_source);
	unsigned int fragmentshader = Shader::CreateShader(GL_FRAGMENT_SHADER, this->m_fragement_shader_source);

	//put the shader into program
	glAttachShader(this->m_program, vertexshader);
	glAttachShader(this->m_program, fragmentshader);

	//link the program
	glLinkProgram(this->m_program);


	//TODO : ERROR
	int success;
	glGetProgramiv(this->m_program, GL_LINK_STATUS, &success);
	if (!success) {
		int length;
		glGetProgramiv(this->m_program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(sizeof(char) * length);
		glGetProgramInfoLog(this->m_program, length, &length, message);
		std::cout << "Failed to link program! " << std::endl;
		std::cout << "Error info : " << message << std::endl;
	}
	//END: TODO: ERROR


	glDeleteShader(vertexshader);
	glDeleteShader(fragmentshader);


}


unsigned int Shader::CreateShader(unsigned int type, const std::string& shadersource) {
	//FUNCTION 
	const char* ss = shadersource.c_str();
	// create shader
	unsigned int shader =  glCreateShader(type);

	//put the source into shader
	glShaderSource(shader, 1, &ss, nullptr);

	//compile shader
	glCompileShader(shader);

	//TODO : ERROR
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		//compile error
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);

		//print the error message
		std::cout << "Failed to compile " << type << " shader!" << std::endl;
		if (type == 35633) {
			std::cout << "Vertex" << " Shader Error : " << message << std::endl;
		}
		else if (type == 35632) {
			std::cout << "Fragment" << " Shader Error : " << message << std::endl;
		}

		return 0;
	}
	return shader;
}


void Shader::ParseShader() {
	//FUNCTION
	std::ifstream stream(this->m_shader_file_path);
	std::string line;
	ShaderSource::ShaderType type = ShaderSource::ShaderType::NONE;
	std::stringstream ss[2];
	while (std::getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				//vertex shader text
				type = ShaderSource::ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				//fragment shader text
				type = ShaderSource::ShaderType::FRAGMENT;
			}
		}
		else {
			ss[int(type)] << line << std::endl;
		}
	}
	this->m_vertex_shader_source = ss[0].str();
	this->m_fragement_shader_source = ss[1].str();
}

void Shader::UseProgram() {
	glUseProgram(this->m_program);
}

void Shader::BindTexture(unsigned int type, unsigned int texture_id)
{
	glBindTexture(type, texture_id);
}

int Shader::GetUniformLoaction(const char* name)
{
	return glGetUniformLocation(this->m_program, name);
}

void Shader::SetInt(const char* name, const int value)
{
	int location = glGetUniformLocation(this->m_program, name);
	glUniform1i(location, value);
}

void Shader::SetMat4f(const char* name, const glm::mat4 matrix)
{
	int location = glGetUniformLocation(this->m_program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetFloat(const char* name, const float value)
{
	int location = glGetUniformLocation(this->m_program, name);
	glUniform1f(location, value);
}


