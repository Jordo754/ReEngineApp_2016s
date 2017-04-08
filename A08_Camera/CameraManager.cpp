#include "CameraManager.h";



CameraManager::CameraManager()
{
	m_v3Position = vector3(0, 0, 2);
	m_v3Target = vector3(0, 0, 3);
	m_v3Up = vector3(0, 1, 0);

	m_v3Front = glm::normalize(m_v3Position - m_v3Target);
	m_v3Right = glm::normalize(glm::cross(vector3(0.0f, 1.0f, 0.0f), m_v3Front));

	fPitch = 0.0f;
	fYaw = 0.0f;
	fRoll = 0.0f;
}

CameraManager::CameraManager(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Up)
{
	m_v3Position = a_v3Position;
	m_v3Target = a_v3Target;
	m_v3Up = glm::normalize(a_v3Up);

	m_v3Front = glm::normalize(m_v3Position - m_v3Target);
	m_v3Right = glm::normalize(glm::cross(m_v3Up, m_v3Front));

}

matrix4 CameraManager::GetView()
{
	m_v3Front = glm::normalize(m_v3Position - m_v3Target);
	m_v3Right = glm::normalize(glm::cross(m_v3Up, m_v3Front));
	m_v3Up = glm::normalize(glm::cross(m_v3Front, m_v3Right));

	quaternion qPitch = glm::angleAxis(fPitch, m_v3Right);
	quaternion qYaw = glm::angleAxis(fYaw, m_v3Up);
	quaternion qRoll = glm::angleAxis(fRoll, m_v3Front);

	quaternion orientation = qPitch * qYaw * qRoll;
	orientation = glm::normalize(orientation);
	matrix4 m4Rotate = ToMatrix4(orientation);

	matrix4 m4Translate = glm::mat4(1.0f);
	m4Translate = glm::translate(m4Translate, -m_v3Target);

	m4View = m4Rotate * m4Translate;

	return m4View;
}

matrix4 CameraManager::GetProjection(bool bOrtographic)
{
	if (bOrtographic)
	{
		m4Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 5.0f, 100.0f);
	}

	else
	{
		m4Projection = glm::perspective(45.0f, (GLfloat)800 / (GLfloat)600, 0.1f, 100.0f);
	}

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
	m_v3Position.z -= fIncrement;
	m_v3Target.z -= fIncrement;
}

void CameraManager::MoveSideways(float fIncrement)
{
	m_v3Position.x += fIncrement;
	m_v3Target.x += fIncrement;
}

void CameraManager::MoveVertical(float fIncrement)
{
	m_v3Position.y += fIncrement;
	m_v3Target.y += fIncrement;
}

void CameraManager::ChangePitch(float fIncrement)
{
	fPitch += fIncrement;
}

void CameraManager::ChangeRoll(float fIncrement)
{
	fRoll += fIncrement;
}

void CameraManager::ChangeYaw(float fIncrement)
{
	fYaw += fIncrement;
}
