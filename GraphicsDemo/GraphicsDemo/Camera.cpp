#include "Camera.h"
#include "Dependencies/SDL2/include/SDL.h"

Camera::Camera() :
	m_cameraPos(glm::vec3(0.0f, 0.0f, 1.0f)),
	m_cameraForward(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_cameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_cameraSpeed(2.5f)
{
	m_cameraRight = glm::normalize(glm::cross(m_cameraUpVector, -m_cameraForward));
}

Camera::~Camera()
{
}

void Camera::InitCameraPerspective(float fov, float aspectRatio, float near, float far)
{
	m_projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

void Camera::InitCameraOrthographic(float left, float right, float bottom, float up, float near, float far)
{
	m_projection = glm::ortho(left, right, bottom, up, near, far);
}

void Camera::MoveForward(float dt)
{
	m_cameraPos += (m_cameraSpeed * dt) * m_cameraForward;
}

void Camera::MoveBackward(float dt)
{
	m_cameraPos -= (m_cameraSpeed * dt) * m_cameraForward;
}

void Camera::StrafeLeft(float dt)
{
	glm::vec3 StrafteDirection = glm::cross(m_cameraForward, m_cameraUpVector);
	m_cameraPos -= (m_cameraSpeed * dt) * StrafteDirection;
}

void Camera::StrafeRight(float dt)
{
	glm::vec3 StrafteDirection = glm::cross(m_cameraForward, m_cameraUpVector);
	m_cameraPos += (m_cameraSpeed * dt) * StrafteDirection;
}

void Camera::Rise(float dt)
{
	m_cameraPos += (m_cameraSpeed * dt) * m_cameraUpVector;
}

void Camera::Fall(float dt)
{
	m_cameraPos -= (m_cameraSpeed * dt) * m_cameraUpVector;
}

void Camera::MouseUpdate(const glm::vec2& newMousePos, float dt)
{
	glm::vec2 MouseDelta = newMousePos - m_oldMousePos;

	if (glm::length(MouseDelta) > 50.0f)
	{
		m_oldMousePos = newMousePos;
		return;
	}

	const float ROTATION_SPEED = 15.0f;
	glm::vec3 RotateAround = glm::cross(m_cameraForward, m_cameraUpVector);

	m_cameraForward = glm::mat3(glm::rotate(glm::radians(-MouseDelta.x) * ROTATION_SPEED * dt, m_cameraUpVector)) * m_cameraForward;
	m_cameraForward = glm::mat3(glm::rotate(glm::radians(-MouseDelta.y) * ROTATION_SPEED * dt, RotateAround)) * m_cameraForward;

	m_oldMousePos = newMousePos;
}

void Camera::Update()
{
	m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraForward, m_cameraUpVector);
}