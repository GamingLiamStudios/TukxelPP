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

#include "Math.hpp"

class Camera {
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront, cameraUp;
	glm::vec3 direction;
	float yaw, pitch, roll;

	Camera() {
		cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		pitch = roll = 0.0f;
		float yaw = -90.0f;

		direction.x = FMath::cos(glm::radians(yaw)) * FMath::cos(glm::radians(pitch));
		direction.y = FMath::sin(glm::radians(pitch));
		direction.z = FMath::sin(glm::radians(yaw)) * FMath::cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);
	}

	glm::mat4 GetLookAt(){
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	void HandleKeyboardInput(GLFWwindow* window, float deltaTime) {
		float cameraSpeed = 2.5f * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	void HandleMouseInput(float mouseDifX, float mouseDifY) {
		yaw += mouseDifX;
		pitch += mouseDifY;

		std::cout << -360.0f * (yaw > 360) + 360.0f * (yaw < 0) << std::endl;

		pitch = -89.9f * (pitch < -89.9f) + 89.9f * (pitch > 89.9f) + pitch * (pitch >= -89.9f && pitch <= 89.9f);
		yaw += -360.0f * (yaw > 360) + 360.0f * (yaw < 0);

		std::cout << "yaw: " << yaw << "; pitch: " << pitch << std::endl;

		direction.x = FMath::cos(glm::radians(yaw)) * FMath::cos(glm::radians(pitch));
		direction.y = FMath::sin(glm::radians(pitch));
		direction.z = FMath::sin(glm::radians(yaw)) * FMath::cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);
	}
};

#endif