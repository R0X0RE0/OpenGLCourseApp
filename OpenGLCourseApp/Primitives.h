#pragma once

#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
class Primitives
{
public:
	Primitives();
	Primitives(int vCount, int iCount);
	GLfloat* cubeVertices = new GLfloat[64]{
		// x, y, z, u, v, nx, ny, nz
		-1.0f, -1.0f, 1.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, //0
		-1.0f, 1.0f, 1.0f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, // 1
		1.0f, -1.0f, 1.0f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, // 2
		1.0f, 1.0f, 1.0f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, //  3
		-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 4
		-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // 5
		1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 6
		1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f // 7


	};

	unsigned int* cubeIndices = new unsigned int[36]{
		0, 1, 2,
		3, 2, 1,
		0, 2, 4,
		6, 4, 2,
		1, 3, 5,
		7, 5, 3,
		3, 7, 6,
		6, 2, 3,
		1, 5, 4,
		4, 0, 1,
		4, 5, 6,
		7, 6, 5


	};
	
	//Create a set of vertices
	

	~Primitives();

private:
	int vertexCount, indexCount;
};

