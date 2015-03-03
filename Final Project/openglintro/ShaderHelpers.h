#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <fstream>
#include <iostream>

using namespace std;
using namespace glm;

// loadTextFile function declaration
char* loadTextFile(const char* file);

// loadShader function declaration
GLuint loadShader(const char* file, GLenum shaderType);

// loadShader function declaration
GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);

// setShaderColor function declaration 
void setShaderColor(GLuint shaderPrgmIndex, const char* varName, float rValue, float gValue, float bValue);

// setShaderMatrix function declaration
void setShaderMatrix(GLuint shaderPrgmIndex, const char* varName, mat4 transform);
