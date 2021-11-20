/*To-Do List*/
// Create a Primitives Class for different objects

// Created by Dylan Hawley 2021


#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Primitives.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

using namespace glm;
using namespace std;


const float TO_RADIANS = 3.14159265f / 180.0f;

Window mainWindow;
vector<Mesh*> meshList;

Mesh meshPrimitive;

Primitives primitive;
vector<Shader> shaderList;
Camera camera;

Light mainLight;

Texture dirtTexture, brickTexture;

GLfloat deltaTime = 0.0f, initialTime = 0.0f;

// Uniform Variables
float triOffset;
float ambientOffset, rOffset, gOffset, bOffset;




//Vertex Shader
static const char* VERTEX_SHADER = "Shaders/shader.vert";

//Fragment Shader
static const char* FRAGMENT_SHADER = "Shaders/shader.frag";

void calcAverageNormals(unsigned int * indices, unsigned int indexCount, GLfloat * vertices, unsigned int vertexCount, unsigned int vLength, unsigned int normalOffset) {
	for (size_t i = 0; i < indexCount; i += 3) {
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		
		vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		vec3 normal = cross(v1, v2);
		normal = normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}
	for (size_t i = 0; i < vertexCount / vLength; i++) {
		unsigned int nOffset = i * vLength + normalOffset;
		vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}







void createShaders() {
	Shader *shader1 = new Shader();
	shader1->createFromFiles(VERTEX_SHADER, FRAGMENT_SHADER);
	shaderList.push_back(*shader1);
}


float u1 = 1.0f, v1 = 1.0f;
float u2 = 1.0f, v2 = -1.0f;
float u3 = -1.0f, v3 = 1.0f;
float u4 = -1.0f, v4 = -1.0f;

void createRoomEssentials(int numRooms) {
	GLfloat vertices[] = {
		// x, y, z, u, v, nx, ny, nz
		-1.0f, -1.0f, 1.0f, u1, v1, -1.0f, -1.0f, 1.0f, //0
		-1.0f, 1.0f, 1.0f, u2, v2, -1.0f, 1.0f, 1.0f, // 1
		1.0f, -1.0f, 1.0f, u3, v3, 1.0f, -1.0f, 1.0f, // 2
		1.0f, 1.0f, 1.0f, u4, v4, 1.0f, 1.0f, 1.0f/*, //  3
		-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, -1.0f, // 4
		-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, // 5
		1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, -1.0f, // 6
		1.0f, 1.0f, -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f*/ // 7


	};
	unsigned int indices[] = {
		0, 1, 2,
		3, 2, 1/*,
		0, 2, 4,
		6, 4, 2,
		1, 3, 5,
		7, 5, 3,
		3, 7, 6,
		6, 2, 3,
		1, 5, 4,
		4, 0, 1,
		4, 5, 6,
		7, 6, 5*/


	};


	calcAverageNormals(indices, 6, vertices, 32, 8, 5);


	for (int i = 0; i < numRooms; i++) {
		Mesh* obj1 = new Mesh();
		obj1->createMesh(vertices, indices, sizeof(vertices), sizeof(indices));
		meshList.push_back(obj1);

		Mesh* obj2 = new Mesh();
		obj2->createMesh(vertices, indices, sizeof(vertices), sizeof(indices));
		meshList.push_back(obj2);

		Mesh* obj3 = new Mesh();
		obj3->createMesh(vertices, indices, sizeof(vertices), sizeof(indices));
		meshList.push_back(obj3);

		Mesh* obj4 = new Mesh();
		obj4->createMesh(vertices, indices, sizeof(vertices), sizeof(indices));
		meshList.push_back(obj4);

		Mesh* obj5 = new Mesh();
		obj5->createMesh(vertices, indices, sizeof(vertices), sizeof(indices));
		meshList.push_back(obj5);
	}

}
void createRoom(int roomID, GLuint uniModel, GLuint uniProjection, GLuint uniView, GLuint uniSpecView, float roomPosX, float roomPosY, float roomPosZ, float roomScaleX, float roomScaleY, float roomScaleZ) {
	
	uniModel = shaderList[0].getModelLocation();
	uniProjection = shaderList[0].getProjectionLocation();
	uniView = shaderList[0].getViewLocation();
	uniSpecView = shaderList[0].getSpecularViewLocation();

	int roomNth = -1;
	for (int i = 0; i < roomID; i++) {
		roomNth += 5;
	}
		
	

	mat4 projection = perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	mat4 model(1.0f);
	
	model = translate(model, vec3((0.0f + roomPosX) * roomScaleX, (0.2f + roomPosY) * (roomScaleY * 1.5f) * roomScaleY, (-1.0f + roomPosZ) * roomScaleZ - 0.2));
	model = scale(model, vec3(1.0f * roomScaleX, 1.0f * roomScaleY, 0.2f));
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(uniProjection, 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(uniView, 1, GL_FALSE, value_ptr(camera.calculateViewMatrix()));
	
	brickTexture.useTexture();
	meshList[1 + roomNth + roomID]->renderMesh();

	model = mat4(1.0f);
	model = translate(model, vec3((-1.0f + roomPosX) * roomScaleX - 0.2, (0.2f + roomPosY) * (roomScaleY * 1.5f) * roomScaleY, (0.0f + roomPosZ) * roomScaleZ));
	model = rotate(model, 90.0f * TO_RADIANS, vec3(0.0f, 1.0f, 0.0f));
	model = scale(model, vec3(1.0 * roomScaleZ, 1.0f * roomScaleY, 0.2));
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, value_ptr(model));
	brickTexture.useTexture();
	meshList[2 + roomNth + roomID]->renderMesh();

	model = mat4(1.0f);
	model = translate(model, vec3((0.0f + roomPosX) * roomScaleX, (0.2f + roomPosY) * (roomScaleY * 1.5f) * roomScaleY, (1.0f + roomPosZ) * roomScaleZ - 0.2));
	model = scale(model, vec3(1.0f * roomScaleX, 1.0f * roomScaleY, 0.2f));
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, value_ptr(model));
	brickTexture.useTexture();
	meshList[3 + roomNth + roomID]->renderMesh();

	model = mat4(1.0f);
	model = translate(model, vec3((1.0f + roomPosX) * roomScaleX - 0.2, (0.2f + roomPosY) * (roomScaleY * 1.5f) * roomScaleY, (0.0f + roomPosZ) * roomScaleZ));
	model = rotate(model, 90.0f * TO_RADIANS, vec3(0.0f, 1.0f, 0.0f));
	model = scale(model, vec3(1.0 * roomScaleZ, 1.0f * roomScaleY, 0.2));
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, value_ptr(model));
	brickTexture.useTexture();
	meshList[4 + roomNth + roomID]->renderMesh();

	model = mat4(1.0f);
	model = translate(model, vec3((0.0f + roomPosX) * roomScaleX, (-0.1f + roomPosY) * (roomScaleY * 1.5f) * roomScaleY, (0.0f + roomPosZ) * roomScaleZ));
	model = scale(model, vec3(1.0f * roomScaleX, 0.2f, 1.0f * roomScaleZ));
	model = rotate(model, 90.0f * TO_RADIANS, vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, value_ptr(model));
	dirtTexture.useTexture();
	meshList[5 + roomNth + roomID]->renderMesh();

}
int main()
{
	bool fullbright;
	GLfloat uiAmbientIntensity, uiDiffuseIntensity, uiSpecularIntensity;
	/*cout << "Graphics Options";
	cout << "\n\nFullbright... 1 to turn on, 0 to turn off...\n";
	cin >> fullbright;
	if (!fullbright) {
		cout << "\n\nAmbient intensity...\n";
		cin >> uiAmbientIntensity;
		cout << "\n\nDiffuse intensity...\n";
		cin >> uiDiffuseIntensity;
		cout << "\n\nSpecular intensity...\n";
		cin >> uiSpecularIntensity;
	}*/
	mainWindow = Window(1280, 720);
	mainWindow.initialize();

	camera = Camera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 1.0f);
	//if (camera.position == meshList[0].) {

	//}

	brickTexture = Texture("Textures/brick.png");
	brickTexture.loadTexture();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.loadTexture();
	//ambientOffset = 1.0f;
	
	//Create a triangle
	//createObjects();
	createRoomEssentials(7);
	cout << meshList[1]->getVAO();
	createShaders();

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformAmbientColor = 0, uniformAmbientIntensity = 0, uniformDiffuseIntensity = 0, uniformDirection = 0, uniformSpecularReflection = 0, uniformSpecularView = 0, uniformSpecularIntensity = 0;
	
	mat4 projection = perspective(45.0f, mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	GLfloat diffuseX = 0.0f, diffuseY = 0.0f, diffuseZ = 0.0f;

	const float AINTENSITY = 1.0f, DINTENSITY = 1.0f, SINTENSITY = 1.0f;
	// Loop until window is closed
	while (!mainWindow.getShouldClose()) {
		
		//if (!fullbright) mainLight = Light(1.0f, 1.0f, 1.0f, uiAmbientIntensity, -0.5f, 1.0f, 0.6f, uiDiffuseIntensity, -camera.position.x, -camera.position.y, 0.0f, camera.position.x, camera.position.y, camera.position.z, uiSpecularIntensity);
		// red, green, blue, ambient intensity, x direction, y direction, z direction, diffuse intensity, x reflection, y reflection, z reflection, x view, y view, z view, specular intensity
		mainLight = Light(1.0f, 1.0f, 1.0f, AINTENSITY, 2.0f, 0.25f, 2.0f, DINTENSITY, -mainLight.direction.x, -mainLight.direction.y, -mainLight.direction.z, camera.position.x, camera.position.y, camera.position.z, SINTENSITY);

		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - initialTime;
		initialTime = currentTime;

		//mainLight = Light(1.0f, 1.0f, 0.8f, ambientOffset);
		triOffset += 0.1f;
		/*if (ambientOffset <= 1.1f) {
			ambientOffset -= 0.01f;

		}
		if (ambientOffset >= 0.2f) {
			ambientOffset += 0.01f;

		}*/

		// Get and handle user input events
		glfwPollEvents();

		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		bool* keys = mainWindow.getKeys();
		if (keys[GLFW_KEY_SPACE]) {
			camera.position.y += 0.005f;
		}
		else if (camera.position.y <= 1.5f) {
			camera.position.y = 1.5f;
		}
		else if (camera.position.y != 1.5f) {
			camera.position.y -= 0.005f;
		}
		
		//Clear window
		glClearColor(0.19f, 0.42f, 0.67f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Use the shader program
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectionLocation();
		uniformView = shaderList[0].getViewLocation();
		uniformAmbientColor = shaderList[0].getAmbientColorLocation();
		uniformAmbientIntensity = shaderList[0].getAmbientIntensityLocation();
		uniformDiffuseIntensity = shaderList[0].getDiffuseIntensityLocation();
		uniformDirection = shaderList[0].getDirectionLocation();
		uniformSpecularReflection = shaderList[0].getSpecularReflectionLocation();
		uniformSpecularView = shaderList[0].getSpecularViewLocation();
		uniformSpecularIntensity = shaderList[0].getSpecularIntensityLocation();

		mainLight.useLight(uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection, uniformSpecularReflection, uniformSpecularView, uniformSpecularIntensity);

		

		createRoom(0, uniformModel, uniformProjection, uniformView, uniformSpecularView, 0.0f, 0.0f, 0.25f, 2.0f, 2.0f, 4.0f);
		createRoom(1, uniformModel, uniformProjection, uniformView, uniformSpecularView, 0.0f, 0.0f, 3.5f, 10.0f, 2.0f, 2.0f);
		createRoom(2, uniformModel, uniformProjection, uniformView, uniformSpecularView, -1.5f, 0.0f, 0.25f, 4.0f, 2.0f, 4.0f);
		createRoom(3, uniformModel, uniformProjection, uniformView, uniformSpecularView, 1.5f, 0.0f, 0.25f, 4.0f, 2.0f, 4.0f);
		createRoom(4, uniformModel, uniformProjection, uniformView, uniformSpecularView, 0.0f, 0.0f, -1.5f, 10.0f, 2.0f, 6.0f);
		createRoom(5, uniformModel, uniformProjection, uniformView, uniformSpecularView, 0.0f, 0.0f, -3.5f, 10.0f, 2.0f, 6.0f);
		
		
		
		meshList[2]->clearMesh();
		meshList[0]->clearMesh();
		meshList[6]->clearMesh();
		meshList[12]->clearMesh();
		meshList[18]->clearMesh();
		meshList[26]->clearMesh();

		

		//Unbind
		glUseProgram(0);

		mainWindow.swapBuffers();
	}
	


	return 0;
}