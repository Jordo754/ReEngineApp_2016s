#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;
	nIndex = 0;
	m_m4Walleye = glm::translate(vector3(-4.0f, -2.0f, 5.0f));
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	m_pMeshMngr->SetModelMatrix(m_m4Walleye, "WallEye");

	float fTimer = 0.0f;
	static DWORD timerSinceBoot = GetTickCount();
	DWORD timerSinceStart = GetTickCount() - timerSinceBoot;
	fTimer = timerSinceStart / 1000.0f;
	float percent = fmod(fTimer, fDuration) / fDuration;

	std::vector<vector3> points;
	points.push_back(vector3(-4.0f, -2.0f, 5.0f));
	points.push_back(vector3(1.0f, -2.0f, 5.0f));
	points.push_back(vector3(-3.0f, -1.0f, 3.0f));
	points.push_back(vector3(2.0f, -1.0f, 3.0f));
	points.push_back(vector3(-2.0f, 0.0f, 0.0f));
	points.push_back(vector3(3.0f, 0.0f, 0.0f));
	points.push_back(vector3(-1.0f, 1.0f, -3.0f));
	points.push_back(vector3(4.0f, 1.0f, -3.0f));
	points.push_back(vector3(0.0f, 2.0f, -5.0f));
	points.push_back(vector3(5.0f, 2.0f, -5.0f));
	points.push_back(vector3(1.0f, 3.0f, -5.0f));

	for (int i = 0; i < points.size(); i++)
	{
		m_pMeshMngr->AddSphereToRenderList(glm::translate(points[i]) * glm::scale(vector3(0.1)), RERED, SOLID);
	}

	if (fmod(fTimer, fDuration) == 0)
	{
		nIndex++;
		if (nIndex == points.size())
		{
			nIndex = 0;
		}
	}

	//glm::lerp(v3Start, v3End, fPercent)
	if (nIndex != points.size() - 1)
	{
		m_m4Walleye = glm::translate(glm::lerp(points[nIndex], points[nIndex + 1], percent));
	}

	else
	{
		m_m4Walleye = glm::translate(glm::lerp(points[nIndex], points[0], percent));
	}
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);

	m_pMeshMngr->PrintLine(std::to_string(fTimer));
	fTimer += 0.016;
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}