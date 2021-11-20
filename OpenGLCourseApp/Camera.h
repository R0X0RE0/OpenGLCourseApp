#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc\matrix_transform.hpp>
#include <GLFW/glfw3.h>

using namespace glm;

class Camera
{
public:
	Camera();
	Camera(vec3 startPosition, vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed, GLfloat startTurnSpeed);
	
	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	mat4 calculateViewMatrix();
	vec3 position;
	vec3 rotation;

	~Camera();

private:
	vec3 front, up, right, worldUp;

	GLfloat yaw, pitch, movementSpeed, turnSpeed;

	void update();
};

