#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <glad/glad.h>
using namespace std;
// Class to simplify dealing with shaders
class Shader {

public:
	unsigned int program;
	Shader(const char *vertexPath, const char* fragmentPath) {
		string vertexCode, fragmentCode;
		ifstream vertexShaderFile;
		ifstream fragmentShaderFile;
		vertexShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		fragmentShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		try {
			vertexShaderFile.open(vertexPath);
			fragmentShaderFile.open(fragmentPath);
			stringstream vertexBuffer, fragmentBuffer;
			vertexBuffer << vertexShaderFile.rdbuf();
			vertexBuffer << fragmentShaderFile.rdbuf();
			vertexCode = vertexBuffer.str();
			fragmentCode = fragmentBuffer.str();
		}
		catch (ifstream::failure e) {
			cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;
		}
		const char *vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();
		// Create the shaders
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);
		// Might want to consider something that confirms successful compilation

		// Create the program that the shaders are then attatched to
		program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		// Shaders are no longer needed, code has been loaded into program
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
};