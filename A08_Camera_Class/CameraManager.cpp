#include "CameraManager.h";

matrix4 CameraManager::GetView()
{
	vector3 cameraDirection = glm::normalize(m_v3Position - m_v3Target);
	vector3 cameraRight = glm::normalize(glm::cross(vector3(0.0f, 1.0f, 0.0f), cameraDirection));
	vector3 cameraUp = glm::cross(cameraDirection, cameraRight);

	m4View = glm::lookAt(cameraRight, cameraUp, cameraDirection);

	return m4View;
}

matrix4 CameraManager::GetProjection(bool bOrtographic)
{
	return m4Projection;
}

void CameraManager::SetPosition(vector3 v3Position)
{
	m_v3Position = v3Position;
}

void CameraManager::SetTarget(vector3 v3Target)
{
	m_v3Target = v3Target;
}

void CameraManager::SetUp(vector3 v3Up)
{
	m_v3Up = v3Up;
}

void CameraManager::MoveForward(float fIncrement)
{
	m_v3Position += fIncrement * m_v3Front;
}

void CameraManager::MoveSideways(float fIncrement)
{
	m_v3Position += glm::normalize(glm::cross(m_v3Front, m_v3Up)) * fIncrement;
}

void CameraManager::MoveVertical(float fIncrement)
{

}

void CameraManager::ChangePitch(float fIncrement)
{

}

void CameraManager::ChangeRoll(float fIncrement)
{

}

void CameraManager::ChangeYaw(float fIncrement)
{

}
