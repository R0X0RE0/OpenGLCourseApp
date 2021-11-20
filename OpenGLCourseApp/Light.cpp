#include "Light.h"

Light::Light() {
	Camera camera;
	color = vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 0.4f;

	direction = vec3(-0.5f, 1.0f, 0.6f);
	diffuseIntensity = 0.4f;

	reflection = vec3(-direction.x, -direction.y, -direction.z);
	viewPos = vec3(camera.position.x, camera.position.y, camera.position.z);
	specularIntensity = 0.0002f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
	GLfloat xDirection, GLfloat yDirection, GLfloat zDirection, GLfloat dIntensity,
	GLfloat reflectX, GLfloat reflectY, GLfloat reflectZ,
	GLfloat viewX, GLfloat viewY, GLfloat viewZ, GLfloat sIntensity) {
	color = vec3(red, green, blue);
	ambientIntensity = aIntensity;

	direction = vec3(xDirection, yDirection, zDirection);
	diffuseIntensity = dIntensity;

	reflection = vec3(reflectX, reflectY, reflectZ);
	viewPos = vec3(viewX, viewY, viewZ);
	specularIntensity = sIntensity;

}

void Light::useLight(GLfloat ambientIntensityLoc, GLfloat ambientColorLoc,
	GLfloat diffuseIntensityLoc, GLfloat directionLoc,
	GLfloat specularReflectionLoc, GLfloat specularViewLoc, GLfloat specularIntensityLoc) {
	glUniform3f(ambientColorLoc, color.x, color.y, color.z);
	glUniform1f(ambientIntensityLoc, ambientIntensity);
	glUniform3f(directionLoc, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLoc, diffuseIntensity);
	glUniform3f(specularReflectionLoc, reflection.x, reflection.y, reflection.z);
	glUniform3f(specularViewLoc, viewPos.x, viewPos.y, viewPos.z);
	glUniform1f(specularIntensityLoc, specularIntensity);
}

Light::~Light() {

}