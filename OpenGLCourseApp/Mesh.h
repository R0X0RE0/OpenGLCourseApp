#pragma once

#include <GL/glew.h>



	class Mesh
	{
	public:
		Mesh();

		void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numVertices, unsigned int numIndices);
		void renderMesh();
		GLuint getVAO();
		void clearMesh();
		
		
		~Mesh();
	private:
		GLuint VAO, VBO, IBO;
		GLsizei indexCount;
	};


