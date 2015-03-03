#include "Shape.h"

// Shape constructor defenition - sets up the shape's buffer, vertex array object and various variables
Shape::Shape(GLfloat vertexArray[], GLsizei numVertices, GLuint shdrPrgmIndex, float w, float h, BoundingBox* boundBox)
{
	numOfVertices = numVertices;
	shaderProgramIndex = shdrPrgmIndex;

	width = w;
	height = h;

	boundingBox = boundBox;

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(1, &vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numOfVertices * 2, vertexArray, GL_STATIC_DRAW); 

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

// Shape destructor defenition - deletes the vertex buffer object and vertex array object
Shape::~Shape(void)
{
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBufferObject);
}

// Draws the various shapes based on their given shape type and binds the Vertex Array Object
// Types: 1 = triangles, 2 = square or rectangle, 3 = polygon
void Shape::Draw(GLint type)
{
	glBindVertexArray(vertexArrayObject);

	if (type == 1)
	{
		glDrawArrays(GL_TRIANGLES, 0, numOfVertices);
	}
	else if (type == 2)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, numOfVertices);
	}
	else if (type == 3)
	{
		glDrawArrays(GL_LINE_LOOP, 0, numOfVertices);
	}
}

// Returns a transformation matrix created from vec3s passed in through parameters
mat4 Shape::setTransform(vec3 pos, vec3 rot, vec3 sclr, float rotAngle)
{
	position = pos;

	mat4 worldMatrix = translate(pos) * scale(sclr) * rotate(rotAngle, rot);

	return worldMatrix;
}