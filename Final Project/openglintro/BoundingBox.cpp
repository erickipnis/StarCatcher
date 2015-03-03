#include "BoundingBox.h"
#include <iostream>

using namespace std;

// BoundingBox constructor
BoundingBox::BoundingBox(float w, float h)
{
	width = w; 
	height = h;
}

// BoundingBox destructor
BoundingBox::~BoundingBox(void)
{
}

// Splits the Bounding box into 4 sections (top left, top right, bottom left, and bottom right) and checks to see if any section has intersected with another bounding box
// Returns true or false based on results
bool BoundingBox::Contains(BoundingBox* otherBoundingBox)
{
	if (((otherBoundingBox->top < bottom) && (otherBoundingBox->top > top) && (otherBoundingBox->left < right) && (otherBoundingBox->left >left)) || // top left
		((otherBoundingBox->top < bottom) && (otherBoundingBox->top > top) && (otherBoundingBox->right > left) && (otherBoundingBox->right < right)) || // top right
		((otherBoundingBox->bottom > top) && (otherBoundingBox->bottom < bottom) && (otherBoundingBox->left < right) && (otherBoundingBox->left > left)) ||// bottom left
		((otherBoundingBox->bottom > top) && (otherBoundingBox->bottom < bottom) && (otherBoundingBox->right > left) && (otherBoundingBox->right < right)) // bottom right
	   )
	{
		return true;
	}
	else 
	{
		return false;
	}


}

// Calculates the edges of each bounding box from the center of each object (origin) from a given position vec3
void BoundingBox::calculateEdges(vec3 pos)
{
	position = pos;

	top = position.y - (0.5f * height);
	bottom = position.y + (0.5f * height);
	left = position.x - (0.5f * width);
	right = position.x + (0.5f * width);
}