#pragma once
#ifndef CAMERAH
#define CAMERAH

#ifndef GLM_FORCE_SIMD_AVX2
#	define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#	define GLM_FORCE_SIMD_AVX2
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	float Yaw;
	float Pitch;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90, float pitch = 0) : Front(glm::vec3(0.0f, 0.0f, -1.0f)) {
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		UpdateCameraVectors();
	}

	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: Front(glm::vec3(0.0f, 0.0f, -1.0f)) {
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		UpdateCameraVectors();
	}

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(Position, Position + Front, Up);
	}

	void HandleKeyboardInput(GLFWwindow* window, float cameraSpeed) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			Position += cameraSpeed * Front;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			Position -= cameraSpeed * Front;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			Position -= glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			Position += glm::normalize(glm::cross(Front, Up)) * cameraSpeed;
	}

	void HandleMouseInput(float mouseDifX, float mouseDifY) {
		Yaw += mouseDifX;
		Pitch += mouseDifY;

		Pitch = -89.9f * (Pitch < -89.9f) + 89.9f * (Pitch > 89.9f) + Pitch * (Pitch >= -89.9f && Pitch <= 89.9f);
		Yaw += -360.0f * (Yaw > 360) + 360.0f * (Yaw < 0);
		UpdateCameraVectors();
	}

private:
	void UpdateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);

		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}

};

#endif