#pragma once
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;




class Camera
{
private:
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp;
		float yaw;
		float pitch;
		float movementSpeed;
		float mouseSensitivity;
		float zoom;
		void updateCameraVectors();

public:
	
	const float getZoom() const { return zoom; }
	const glm::vec3 getPosition() const { return position; }
	const glm::vec3 getFront() const { return front; }
	const glm::vec3 getUp() const { return up; }
	const glm::vec3 getRight() const { return right; }
	const float getPitch() const { return pitch; }
	const float getYaw() const { return yaw; }
	const float getSpeed() const { return movementSpeed; }
	const float getSensitivity() const { return mouseSensitivity; }

	//initializes with a initializer list
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH)
		: position(position), worldUp(up), yaw(yaw), pitch(pitch), front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		updateCameraVectors();
	}
	//initializes with a initializer list
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
		: position(posX, posY, posZ), worldUp(upX, upY, upZ), yaw(yaw), pitch(pitch),
		front(0.0f, 0.0f, -1.0f), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM)
	{
		updateCameraVectors();
	}
	// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 getViewMatrix();
	
	// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void processKeyboard(Camera_Movement direction, float deltaTime);
	
	// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

	// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset);

	void SetSpeed(float speed);

	void SetSensitivity(float sensitivity);
};


