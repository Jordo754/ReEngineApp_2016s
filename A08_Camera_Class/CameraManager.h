#pragma once

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class CameraManager : public ReEngAppClass
{
private:
	matrix4 m4View;
	matrix4 m4Projection;
	
	vector3 m_v3Position;
	vector3 m_v3Target;
	vector3 m_v3Up;
	vector3 m_v3Front;

public:
	//methods
	//should get the view matrix
	matrix4 GetView();

	//should get the projection matrix
	matrix4 GetProjection(bool bOrtographic);

	//sets the position of the camera
	void SetPosition(vector3 v3Position);

	//sets the target of the camera
	void SetTarget(vector3 v3Target);

	//sets the up vector of the camera
	void SetUp(vector3 v3Up);

	//move the camera forward or backwards depending on the view vector
	void MoveForward(float fIncrement);

	//move the camera based on the right vector depending on the view vector
	void MoveSideways(float fIncrement);

	//move the camera up or down depending on the up vector
	void MoveVertical(float fIncrement);

	//orient your camera meaning forward and up chaning its angle x
	void ChangePitch(float fIncrement);

	//orient your camera meaning forward and up chaning its angle z
	void ChangeRoll(float fIncrement);

	//orient your camera meaning forward and up chaning its angle y
	void ChangeYaw(float fIncrement);
};