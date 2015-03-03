// Eric Kipnis
// DSA 1 - Final Project

#include <vector>
#include <time.h>
#include "ShaderHelpers.h"
#include "Shape.h"
#include "Entity.h"
#include "BoundingBox.h"

using namespace std;

// Global shader program index
GLuint shaderProgram;

// Global shape pointers
Shape* trianglePointer;
Shape* squarePointer;
Shape* starPointer;
Shape* rectanglePointer;

// Global BoundingBox pointers
BoundingBox* paddleBoundingBox;
BoundingBox* roofBoundingBox;
BoundingBox* baseBoundingBox;

//Global Entity Pointer
Entity* paddlePointer;

// Global Vectors containing pointers
vector<Entity*> shootingStars;
vector <Shape*> starPointers;
vector <BoundingBox*> starBoundingBoxes;

void init()
{
	cout << "Initializing!" << endl;	

	srand((unsigned int) time(0));

	// Preset vertices for each type of shape
	// width = 0.5f, height = 0.5f
	GLfloat triangleVertices[] = 
	{
		//	X		Y
			0.0f,	0.5f,
		   -0.25f,	0.0f,
		    0.25f,	0.0f
	};

	// width = 0.15f, height = 0.2f
	GLfloat squareVertices[] = 
	{
		//	X			Y
		   -0.075f,		0.1f,
		   -0.075f,	   -0.1f,
		    0.075f,    -0.1f,
			0.075f,		0.1f
	};

	// width = 0.8f, height = 1.0f
	GLfloat starVertices[] = 
	{
		//	X		Y
			0.0f,	0.5f,
		   -0.1f,	0.2f,
		   -0.4f,	0.1f,
		   -0.2f,  -0.1f,
		   -0.3f,  -0.5f,
			0.0f,  -0.2f,
		    0.3f,  -0.5f,
		    0.2f,  -0.1f,
		    0.4f,	0.1f,
		    0.1f,	0.2f
	};		

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Load the shader program
	shaderProgram = loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");

	if (shaderProgram != 0)
	{
		glUseProgram(shaderProgram);
	}
	else
	{
		cout << "Error occurred loading the shader program. Shader could not be loaded." << endl;
	}

	setShaderColor(shaderProgram, "color", 1, 0, 0);

	// Initialize pointers
	paddleBoundingBox = new BoundingBox(0.3f, 0.1f);
	roofBoundingBox = new BoundingBox(0.25f, 0.25f);
	baseBoundingBox = new BoundingBox(0.18f, 0.24f);

	trianglePointer = new Shape(triangleVertices, 3, shaderProgram, 0.25f , 0.25f, roofBoundingBox);
	squarePointer = new Shape(squareVertices, 4, shaderProgram, 0.18f, 0.24f, baseBoundingBox);
	rectanglePointer = new Shape(squareVertices, 4, shaderProgram, 0.3f, 0.1f, paddleBoundingBox);

	paddlePointer = new Entity(rectanglePointer, shaderProgram, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 1), vec3(2.0f, 0.5, 1), 0.0f, 2);

	// randomly assign a shhoting star a rnadom position and velocity direction (left or right)
	for (unsigned int i = 0; i < 10; i++)
	{
		int randNum = rand() % 2 + 1;

		starBoundingBoxes.push_back(new BoundingBox(0.08f, 0.1f));
		starPointers.push_back(new Shape(starVertices, 10, shaderProgram, 0.08f, 0.1f, starBoundingBoxes[i]));

		if (randNum == 1)
		{
			float randPos = (rand() % 19 - 9) / 10.0f;

			shootingStars.push_back(new Entity(starPointers[i], shaderProgram, vec3(0.001, 0, 0), vec3(randPos, 0.9, 0), vec3(0, 0, 1), vec3(0.1, 0.1, 1), 0.0f, 3));
		}
		else if (randNum == 2)
		{
			float randPos = (rand() % 19 - 9) / 10.0f;

			shootingStars.push_back(new Entity(starPointers[i], shaderProgram, vec3(-0.001, 0, 0), vec3(randPos, 0.9, 0), vec3(0, 0, 1), vec3(0.1, 0.1, 1), 0.0f, 3));
		}
	}
}

void update()
{
	// Re-draw the screen the next time through the loop - Uncomment for animation, otherwise it causes lag
	glutPostRedisplay();
}

void draw()
{
	mat4 transform;

	glClear(GL_COLOR_BUFFER_BIT);

	// Bottom green rectangle (grass)
	setShaderColor(shaderProgram, "color", 0, 1, 0);

	transform = squarePointer->setTransform(vec3(0, -0.8f, 0), vec3(0, 0, 1), vec3(13.35f, 2.0f, 1), 0.0f);
	setShaderMatrix(shaderProgram, "worldMatrix", transform);
	squarePointer->Draw(2);

	// Blue squares (houses)
	setShaderColor(shaderProgram, "color", 0, 0, 1);

	transform = squarePointer->setTransform(vec3(-0.8f, -0.6f, 0), vec3(0, 0, 1), vec3(1.2f, 1.2f, 1), 0.0f);
	setShaderMatrix(shaderProgram, "worldMatrix", transform);
	squarePointer->boundingBox->calculateEdges(squarePointer->position);

	for (unsigned int i = 0; i < shootingStars.size(); i++)
	{
		squarePointer->boundingBox->Contains(shootingStars[i]->shapePointer->boundingBox);
	}

	squarePointer->Draw(2);

	transform = squarePointer->setTransform(vec3(-0.25f, -0.6f, 0), vec3(0, 0, 1), vec3(1.2f, 1.2f, 1), 0.0f);
	setShaderMatrix(shaderProgram, "worldMatrix", transform);
	squarePointer->boundingBox->calculateEdges(squarePointer->position);

	for (unsigned int i = 0; i < shootingStars.size(); i++)
	{
		squarePointer->boundingBox->Contains(shootingStars[i]->shapePointer->boundingBox);
	}

	squarePointer->Draw(2);

	transform = squarePointer->setTransform(vec3(0.25f, -0.6f, 0), vec3(0, 0, 1), vec3(1.2f, 1.2f, 1), 0.0f);
	setShaderMatrix(shaderProgram, "worldMatrix", transform);
	squarePointer->boundingBox->calculateEdges(squarePointer->position);

	for (unsigned int i = 0; i < shootingStars.size(); i++)
	{
		squarePointer->boundingBox->Contains(shootingStars[i]->shapePointer->boundingBox);
	}

	squarePointer->Draw(2);

	transform = squarePointer->setTransform(vec3(0.8f, -0.6f, 0), vec3(0, 0, 1), vec3(1.2f, 1.2f, 1), 0.0f);
	setShaderMatrix(shaderProgram, "worldMatrix", transform);
	squarePointer->boundingBox->calculateEdges(squarePointer->position);

	for (unsigned int i = 0; i < shootingStars.size(); i++)
	{
		squarePointer->boundingBox->Contains(shootingStars[i]->shapePointer->boundingBox);
	}

	squarePointer->Draw(2);

	// Red triangles (roofs)
	setShaderColor(shaderProgram, "color", 1, 0, 0);

	transform = trianglePointer->setTransform(vec3(-0.8f, -0.5f, 0), vec3(0, 0, 1), vec3(0.5f, 0.5f, 1), 0.0f);
	setShaderMatrix(shaderProgram, "worldMatrix", transform);
	trianglePointer->boundingBox->calculateEdges(trianglePointer->position);

	for (unsigned int i = 0; i < shootingStars.size(); i++)
	{
		trianglePointer->boundingBox->Contains(shootingStars[i]->shapePointer->boundingBox);
	}

	trianglePointer->Draw(1);

	transform = trianglePointer->setTransform(vec3(-0.25f, -0.5f, 0), vec3(0, 0, 1), vec3(0.5f, 0.5f, 1), 0.0f);
	setShaderMatrix(shaderProgram, "worldMatrix", transform);
	trianglePointer->boundingBox->calculateEdges(trianglePointer->position);

	for (unsigned int i = 0; i < shootingStars.size(); i++)
	{
		trianglePointer->boundingBox->Contains(shootingStars[i]->shapePointer->boundingBox);
	}

	trianglePointer->Draw(1);

	transform = trianglePointer->setTransform(vec3(0.25f, -0.5f, 0), vec3(0, 0, 1), vec3(0.5f, 0.5f, 1), 0.0f);
	setShaderMatrix(shaderProgram, "worldMatrix", transform);
	trianglePointer->boundingBox->calculateEdges(trianglePointer->position);

	for (unsigned int i = 0; i < shootingStars.size(); i++)
	{
		trianglePointer->boundingBox->Contains(shootingStars[i]->shapePointer->boundingBox);
	}

	trianglePointer->Draw(1);

	transform = trianglePointer->setTransform(vec3(0.8f, -0.5f, 0), vec3(0, 0, 1), vec3(0.5f, 0.5f, 1), 0.0f);
	setShaderMatrix(shaderProgram, "worldMatrix", transform);
	trianglePointer->boundingBox->calculateEdges(trianglePointer->position);

	for (unsigned int i = 0; i < shootingStars.size(); i++)
	{
		trianglePointer->boundingBox->Contains(shootingStars[i]->shapePointer->boundingBox);
	}

	trianglePointer->Draw(1);

	// Shooting Stars checks and draw
	setShaderColor(shaderProgram, "color", 1, 1, 1);

	for (unsigned int i = 0; i < shootingStars.size(); i++)
	{
		shootingStars[i]->Update();
		shootingStars[i]->updateForces();
		shootingStars[i]->shapePointer->boundingBox->calculateEdges(shootingStars[i]->position);
		shootingStars[i]->Draw();
	}

	// Paddle checks and draw
	paddlePointer->Update();
	paddlePointer->shapePointer->boundingBox->calculateEdges(paddlePointer->position);

	for (unsigned int i = 0; i < shootingStars.size(); i++)
	{
		if (paddlePointer->shapePointer->boundingBox->Contains(shootingStars[i]->shapePointer->boundingBox))
		{
			shootingStars[i]->position.x = (rand() % 19 - 9) /10.0f;
			shootingStars[i]->position.y = 0.9f;
		}
	}

	paddlePointer->Draw();

	glFlush();
}

void moveMouse(int x, int y)
{
	// convert world coordinates to screen coordinates
	paddlePointer->mousePosition.x = (x / 800.0f) * 2 - 1;
	paddlePointer->mousePosition.y = (y / 600.0f) * 2 - 1;
	paddlePointer->mousePosition.y *= -1;

	// set paddle position to mouse position
	paddlePointer->position.x = paddlePointer->mousePosition.x;
	paddlePointer->position.y = paddlePointer->mousePosition.y;

}

int main (int argc, char* argv[])
{
	glewExperimental = true;

	// Initializes GLUT (and OpenGL)
	glutInit(&argc, argv);

	// Sets the display mode to be a standard image format
	glutInitDisplayMode(GLUT_RGBA);

	// Sets the window size
	glutInitWindowSize(800, 600);

	// Sets which major and minor version of OpenGL to use. 
	glutInitContextVersion(4, 3);

	// Use the core (non-backwards compatible) version of OpenGL
	glutInitContextProfile(GLUT_CORE_PROFILE);

	// Actually creates the window with the specified title
	glutCreateWindow("My first use of OpenGL!");

	if (glewInit() != GLEW_OK) 
	{
		return -1; // GLEW has failed
	}

	// GLUT will call moveMouse() when the mouse moves and no button is clicked
	glutPassiveMotionFunc(moveMouse);	

	// GLUT will call update() when the main loop is idle
	glutIdleFunc(update);

	//GLUT will call draw() when redisplaying the window
	glutDisplayFunc(draw);

	init();

	glutMainLoop();

	// Free allocated memory for the various pointers created
	delete trianglePointer;
	delete squarePointer;
	delete starPointer;
	delete rectanglePointer;

	delete roofBoundingBox;
	delete baseBoundingBox;
	delete paddleBoundingBox;

	delete paddlePointer;

	for (unsigned int i = 0; i < 10; i++)
	{
		// Free allocated memory from pointers in vectors
		delete starBoundingBoxes[i];
		delete starPointers[i];
		delete shootingStars[i];
	}

	return 0;
}