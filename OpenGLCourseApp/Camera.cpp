#include "Camera.h"
#include <iostream>
using namespace glm;
using namespace std;

Camera::Camera() {

}

Camera::Camera(vec3 startPosition, vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed, GLfloat startTurnSpeed) {
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = vec3(0.0f, 0.0f, -1.0f);

	movementSpeed = startMovementSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime) {
	GLfloat velocity = movementSpeed * deltaTime;

	//WASD
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
		position += front * velocity;
		if (keys[GLFW_KEY_LEFT_SHIFT]) {
			position += front * velocity * 3.0f;
		}
		//cout << "You are at " << position.x << ',' << position.y << ',' << position.z << '\n';
	}
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
		position -= front * velocity;
		
	}
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
		position -= right * velocity;
		
	}
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
		position += right * velocity;
	}
	
	
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange) {
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	update();
}
mat4 Camera::calculateViewMatrix() {
	return lookAt(position, position + front, up);
}

void Camera::update() {
	front.x = cos(radians(yaw)) * cos(radians(pitch));
	front.y = sin(radians(pitch));
	front.z = sin(radians(yaw)) * cos(radians(pitch));
	front = normalize(front);

	right = normalize(cross(front, worldUp));
	up = normalize(cross(right, front));
	
	
}

Camera::~Camera() {

}
