#include "ShaderHelpers.h"

// Loads a text file in binary mode containing shader information
// Returns a char* containing all of the data from the file 
char* loadTextFile(const char* file)
{
	ifstream inFile(file, ios::binary);

	if (inFile.is_open())
	{
		// Seek to end of the file and get the file length
		inFile.seekg(0, ios::end);
		int length = (int) inFile.tellg();

		// Seek back to the beginning of the file
		inFile.seekg(0, ios::beg);

		char* fileContents = new char[length + 1];

		inFile.read(fileContents, length);
		fileContents[length] = 0;

		inFile.close();

		return fileContents;
	}
	else
	{
		return 0; // error occurred
	}
}

// Creates and sets up a new shader and keeps track of errors 
// Returns whether the shader successfully loaded or not, 0 = error occured, other = shader index
GLuint loadShader(const char* file, GLenum shaderType)
{
	const char* shaderFileContents;

	if ((shaderFileContents = loadTextFile(file)) != 0)
	{
		GLuint index = glCreateShader(shaderType);
		glShaderSource(index, 1, &shaderFileContents, 0);
		glCompileShader(index);

		delete[] shaderFileContents;

		GLint compileResults;
		glGetShaderiv(index, GL_COMPILE_STATUS, &compileResults);

		if (compileResults == GL_TRUE)
		{
			return index;
		}
		else
		{
			GLint shaderLogLength;
			glGetShaderiv(index, GL_INFO_LOG_LENGTH, &shaderLogLength);

			char* shaderLogContents = new char[shaderLogLength];
			glGetShaderInfoLog(index, shaderLogLength, 0, shaderLogContents);

			cout << shaderLogContents << endl;

			glDeleteShader(index);
			delete[] shaderLogContents;

			return 0;
		}
	}
	else
	{
		cout << "Error loading file." << endl;
		return 0; 
	}
}

// Loads the shaders, creates a shader program and assigns the shaders to the shader program as well as keeping track of errors
// Returns whether the shader program successfully loaded or not, 0 = error occured, other = shader program index
GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	GLuint shaderIndex = loadShader(vertexFile, GL_VERTEX_SHADER);

	if (shaderIndex == 0)
	{
		return 0; 
	}

	GLuint fragmentShaderIndex = loadShader(fragmentFile, GL_FRAGMENT_SHADER);

	if (fragmentShaderIndex == 0)
	{
		return 0;
	}

	GLuint shaderProgramIndex = glCreateProgram();

	glAttachShader(shaderProgramIndex, shaderIndex);
	glAttachShader(shaderProgramIndex, fragmentShaderIndex);

	glLinkProgram(shaderProgramIndex);

	GLint programLinkerResults;
	glGetProgramiv(shaderProgramIndex, GL_LINK_STATUS, &programLinkerResults);

	if (programLinkerResults == GL_TRUE)
	{
		return shaderProgramIndex;
	}
	else
	{
		GLint programLogLength;
		glGetProgramiv(shaderIndex, GL_INFO_LOG_LENGTH, &programLogLength);

		char* programLogContents = new char[programLogLength];
		glGetProgramInfoLog(shaderProgramIndex, programLogLength, 0, programLogContents);

		cout << programLogContents << endl;

		glDeleteProgram(programLogLength);
		delete[] programLogContents;

		return 0;
	}
}

// Sets the current shader color to be used when drawing to the screen by changing a uniform variable
void setShaderColor(GLuint shaderPrgmIndex, const char* varName, float rValue, float gValue, float bValue)
{
	GLint varLocation = glGetUniformLocation(shaderPrgmIndex, varName);

	glProgramUniform4f(shaderPrgmIndex, varLocation, rValue, gValue, bValue, 1.0f);
}

// Sets the current value of the uniform variable "worldMatrix" each time a shape needs to be transformed with matrices
void setShaderMatrix(GLuint shaderPrgmIndex, const char* varName, mat4 transform)
{
	GLint varLocation = glGetUniformLocation(shaderPrgmIndex, varName);
	glProgramUniformMatrix4fv(shaderPrgmIndex, varLocation, 1, GL_FALSE, &transform[0][0]);
}