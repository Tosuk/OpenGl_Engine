#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile; // Vertex Shader File
	std::ifstream fShaderFile; // Fragment Shader File
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexPath); // Open Vertex Shader File
		fShaderFile.open(fragmentPath); // Open Fragment Shader File
		std::stringstream vShaderStream, fShaderStream; // String Stream
		vShaderStream << vShaderFile.rdbuf(); // Read Vertex Shader File	
		fShaderStream << fShaderFile.rdbuf(); // Read Fragment Shader File
		vShaderFile.close(); // Close Vertex Shader File
		fShaderFile.close(); // Close Fragment Shader File
		vertexCode = vShaderStream.str(); // Convert Vertex Shader File to String 
		fragmentCode = fShaderStream.str(); // Convert Fragment Shader File to String
	}
	// if there is an error reading the file
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl; 
	}

	// Convert String to C String
	const char* vShaderCode = vertexCode.c_str(); // Convert Vertex Shader String to C String c string is a null terminated string which is required by OpenGL
	const char* fShaderCode = fragmentCode.c_str(); // Convert Fragment Shader String to C String
	unsigned int vertex, fragment; // Vertex and Fragment Shader ID
	int success;
	char infoLog[512];
	////////Standard OpenGL Shader Compilation////////   like in previous version in main
	vertex = glCreateShader(GL_VERTEX_SHADER); // Create a Vertex Shader
	glShaderSource(vertex, 1, &vShaderCode, NULL); // Attach the Vertex Shader Source Code to the Vertex Shader Object
	glCompileShader(vertex); // Compile the Vertex Shader
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success); // Check if the Vertex Shader Compilation was successful
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER); // Create a Fragment Shader
	glShaderSource(fragment, 1, &fShaderCode, NULL); // Attach the Fragment Shader Source Code to the Fragment Shader Object
	glCompileShader(fragment); // Compile the Fragment Shader
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success); // Check if the Fragment Shader Compilation was successful
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Shader Program
	ID = glCreateProgram(); // Create a Shader Program
	glAttachShader(ID, vertex); // Attach the Vertex Shader to the Shader Program
	glAttachShader(ID, fragment); // Attach the Fragment Shader to the Shader Program
	glLinkProgram(ID); // Link the Shader Program
	glGetProgramiv(ID, GL_LINK_STATUS, &success); // Check if the Shader Program Linking was successful
	if (!success) 
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::Program::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertex); // Delete the Vertex Shader
	glDeleteShader(fragment); // Delete the Fragment Shader
	glDeleteShader(ID); // Delete the Shader Program
}

void Shader::use()
{
	glUseProgram(ID); // Use the Shader Program
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); // Set a Boolean Uniform
}

void Shader::setInt(const std::string& name, int value) const
{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value); // Set an Integer Uniform
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value); // Set a Float Uniform
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); // Set a Vector3 Uniform
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(value)); // Set a Vector3 Uniform
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); // Set a Matrix4 Uniform
}



