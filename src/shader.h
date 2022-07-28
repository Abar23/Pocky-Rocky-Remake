#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "core/utility/GlErrorCheck.h"

class Shader {

public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath) {
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);



			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (std::ifstream::failure& e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCall(glCreateShader, GL_VERTEX_SHADER);
		glCall(glShaderSource, vertex, 1, &vShaderCode, NULL);
		glCall(glCompileShader, vertex);
		checkCompileErrors(vertex, "VERTEX");

		// fragment Shader
		fragment = glCall(glCreateShader, GL_FRAGMENT_SHADER);
		glCall(glShaderSource, fragment, 1, &fShaderCode, NULL);
		glCall(glCompileShader, fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		// shader Program
		ID = glCall(glCreateProgram, );
		glCall(glAttachShader, ID, vertex);
		glCall(glAttachShader, ID, fragment);
		glCall(glLinkProgram, ID);
		checkCompileErrors(ID, "PROGRAM");

		// delete the shaders as they're linked into our program now and no longer necessary
		glCall(glDeleteShader, vertex);
		glCall(glDeleteShader, fragment);



	}

	// activate the shader
	// ------------------------------------------------------------------------
	void use() {
		glCall(glUseProgram, ID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const {
		glCall(glUniform1i, glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const {
		glCall(glUniform1i, glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const {
		glCall(glUniform1f, glGetUniformLocation(ID, name.c_str()), value);
	}

	void setVec4(const std::string& name, float* value) {
		glCall(glUniform4fv, glGetUniformLocation(ID, name.c_str()), 1, &value[0]);

	}

private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type) {
		int success;
		char infoLog[1024];
		if (type != "PROGRAM") {
			glCall(glGetShaderiv, shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glCall(glGetShaderInfoLog, shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else {
			glCall(glGetProgramiv, shader, GL_LINK_STATUS, &success);
			if (!success) {
				glCall(glGetProgramInfoLog, shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}

};



#endif