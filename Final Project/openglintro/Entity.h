#pragma once

// Functions Needed: Move (using matrices), Keyboard, Mouse, Update, Draw

#include "Shape.h"
#include "ShaderHelpers.h"
#include <glm\gtx\transform.hpp>
#include <glm\glm.hpp>

class Entity
{
public:

	// Variable declarations
	Shape* shapePointer;

	GLuint shaderProgramIndex;
	
	GLint shapeType;

	vec3 position;
	vec3 scaler;
	vec3 rotation;
	vec3 mousePosition;
	vec3 velocity;
	vec3 acceleration;

	int previousTime;
	int currentTime;
	int dt;

	float rotationAngle;

	// Entity constructor declaration
	Entity(Shape* shapePntr, GLuint shaderPrgmIndex, vec3 vel, vec3 pos, vec3 rot, vec3 sclr, float rotAngle, GLint shpType);

	// Entity destructor declaration
	~Entity(void);

	//Entity update and draw method declarations
	void Update();
	void Draw();

	// Entity updateForces method declaration
	void updateForces();
};

