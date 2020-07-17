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

class Camera {
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront, cameraUp;

	Camera() {
		cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	glm::mat4 GetLookAt(){
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	void HandleInput(GLFWwindow* window, float deltaTime) {
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
};

#endif