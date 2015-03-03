#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "BoundingBox.h"

using namespace std;
using namespace glm;

class Shape
{
public:

	// Variable declarations
	GLuint vertexBufferObject;
	GLuint vertexArrayObject;
	GLuint shaderProgramIndex;

	GLint offsetLocation;
	GLint scaleLocation;

	GLsizei numOfVertices;

	vec3 position;

	float width;
	float height;

	BoundingBox* boundingBox;

	// Constructor declaration
	Shape(GLfloat vertexArray[], GLsizei numVertices, GLuint shdrPrgmIndex, float w, float h, BoundingBox* boundBox);

	// Destructor declaration
	~Shape(void); 

	// Draw method declaration
	void Draw(GLint type);

	// setTransform declaration
	mat4 setTransform(vec3 pos, vec3 rot, vec3 sclr, float rotAngle);
};

