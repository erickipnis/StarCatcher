#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

class BoundingBox
{
public:

	// Variable declarations
	float width;
	float height;

	float top;
	float bottom;
	float left;
	float right;

	vec3 position;

	// BoundingBox constructor declaration
	BoundingBox(float w, float h);

	// BoundingBox destructor declaration
	~BoundingBox(void);

	// Contains method declaration
	bool Contains(BoundingBox* otherBoundingBox);

	// calculateEdges method declaration
	void calculateEdges(vec3 pos);
};

