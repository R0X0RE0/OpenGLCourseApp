#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include "Camera.h"

using namespace glm;

class Light
{
public:
	Light();

	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
		GLfloat xDirection, GLfloat yDirection, GLfloat zDirection, GLfloat dIntensity,
		GLfloat reflectX, GLfloat reflectY, GLfloat reflectZ,
		GLfloat viewX, GLfloat viewY, GLfloat viewZ, GLfloat sIntensity);

	void useLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc,
		GLfloat diffuseIntensityLoc, GLfloat directionLoc,
		GLfloat specularReflectionLoc, GLfloat specularViewLoc, GLfloat specularIntensityLoc);

	vec3 direction;

	~Light();

private:
	//Ambient
	vec3 color;
	GLfloat ambientIntensity;

	//Diffuse
	
	GLfloat diffuseIntensity;

	//Specular
	vec3 reflection;
	vec3 viewPos;
	GLfloat specularIntensity;
};

