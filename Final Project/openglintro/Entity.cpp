#include "Entity.h"

// Entity constructor, sets initial values for variables
Entity::Entity(Shape* shapePntr, GLuint shaderPrgmIndex, vec3 vel, vec3 pos, vec3 rot, vec3 sclr, float rotAngle, GLint shpType)
{
	shapePointer = shapePntr;
	shaderProgramIndex = shaderPrgmIndex;

	position = pos;
	rotation = rot;
	scaler = sclr;

	mousePosition = vec3(0, 0, 0);
	velocity = vel;
	acceleration = vec3(0, -0.0001f, 0);

	rotationAngle = rotAngle;

	previousTime = 0;
	currentTime = 0;
	dt = 0;

	shapeType = shpType;
}

// Entity destructor
Entity::~Entity(void)
{
}

// Updates the delta time, checks for bounds of stars, and sets the worldMatrix for each entity
void Entity::Update()
{
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	dt = currentTime - previousTime;
	previousTime = currentTime;

	// check if position goes off the screen's left, right, top, and bottom side.
	if (position.x < -0.93f && shapeType == 3)
	{
		position.x = (rand() % 19 - 9) / 10.0f;
		position.y = 0.9f;
	}
	else if (position.x > 0.93f && shapeType == 3)
	{
		position.x = (rand() % 19 - 9) / 10.0f;
		position.y = 0.9f;
	}

	if (position.y < -0.9f && shapeType == 3)
	{
		position.x = (rand() % 19 - 9) / 10.0f;
		position.y = 0.9f;
	}
	else if (position.y > 0.9f && shapeType == 3)
	{
		position.x = (rand() % 19 - 9) / 10.0f;
		position.y = 0.9f;
	}

	mat4 worldMatrix = translate(position) * scale(scaler) * rotate(rotationAngle, rotation);

	setShaderMatrix(shaderProgramIndex, "worldMatrix", worldMatrix);
}

// Calls the entity's shape's draw method
void Entity::Draw()
{
	shapePointer->Draw(shapeType);
}

// Add acceleration to velocity, Add velocity to position (Both Scaled by a scaled delta time)
void Entity::updateForces()
{
	velocity += acceleration * (dt * 0.01f);
	position += velocity * (dt * 0.01f);
}
