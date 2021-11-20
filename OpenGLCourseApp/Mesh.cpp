#include "Mesh.h"


Mesh::Mesh() {
	VAO = 0, VBO = 0, IBO = 0, indexCount = 0;
	

}
void Mesh::createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numVertices, unsigned int numIndices) {
	indexCount = numIndices;
	//Generate and Bind Vertex Arrays
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numIndices, indices, GL_STATIC_DRAW);

	//Generate and Bind Buffers
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Get buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numVertices, vertices, GL_STATIC_DRAW);

	//Get vertex attribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);

	//Enable vertex attribute array
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	//Bind buffer and vertex array again, to zero
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::renderMesh() {
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
GLuint Mesh::getVAO() {
	return VAO;
}
void Mesh::clearMesh(){
	if (IBO != 0) { glDeleteBuffers(1, &IBO); IBO = 0; }
	if (VBO != 0) { glDeleteBuffers(1, &VBO); VBO = 0; }
	if (VAO != 0) { glDeleteVertexArrays(1, &VAO); VAO = 0; }
	indexCount = 0;
}
Mesh::~Mesh() {
	clearMesh();
}