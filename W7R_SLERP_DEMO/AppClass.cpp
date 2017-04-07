#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
<<<<<<< HEAD
	super::InitWindow("Sandbox"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
	m_pSystem->SetWindowResolution(RESOLUTIONS::C_1280x720_16x9_HD);
	//m_pSystem->SetWindowFullscreen(); //Sets the window to be fullscreen
	//m_pSystem->SetWindowBorderless(true); //Sets the window to not have borders
=======
	super::InitWindow("W7R_SLERP_DEMO"); // Window Name
<<<<<<< HEAD
>>>>>>> 1f0255ccf433290ba131bbf9af961a9c4ddf110f
=======
>>>>>>> d5b2223fd6ca24b95c3a20b3621f3644606d7093
>>>>>>> 1841ff349f26c4d02d2ed86ad76903613ed91e74
}

void AppClass::InitVariables(void)
{
<<<<<<< HEAD
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);
=======
<<<<<<< HEAD
>>>>>>> 1f0255ccf433290ba131bbf9af961a9c4ddf110f
=======
>>>>>>> d5b2223fd6ca24b95c3a20b3621f3644606d7093
>>>>>>> 1841ff349f26c4d02d2ed86ad76903613ed91e74
	//Set the camera position
	m_pCameraMngr->SetPositionTargetAndView(
		vector3(0.0f, 2.5f, 15.0f),//Camera position
		vector3(0.0f, 2.5f, 0.0f),//What Im looking at
		REAXISY);//What is up
	//Load a model onto the Mesh manager
<<<<<<< HEAD
	m_pMeshMngr->LoadModel("Lego\\Unikitty.bto", "Unikitty");
=======
	m_pMeshMngr->LoadModel("Minecraft\\Cow.obj", "Cow");
<<<<<<< HEAD
>>>>>>> 1f0255ccf433290ba131bbf9af961a9c4ddf110f
=======
>>>>>>> d5b2223fd6ca24b95c3a20b3621f3644606d7093
>>>>>>> 1841ff349f26c4d02d2ed86ad76903613ed91e74
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
	
	//Set the model matrix for the first model to be the arcball
	m_pMeshMngr->SetModelMatrix(ToMatrix4(m_qArcBall), 0);

<<<<<<< HEAD
	static float fTimer = 0.0f;
	fTimer += m_pSystem->LapClock();
	float fDuration = 5.0f;
	float fPercentage = MapValue(fTimer, 0.0f, fDuration, 0.0f, 1.0f);

	glm::quat q1 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
	quaternion q2 = glm::angleAxis(360.0f, vector3(0.0f, 0.0f, 1.0f));
	quaternion q3 = glm::mix(q1, q2, fPercentage);

	m_pMeshMngr->SetModelMatrix(ToMatrix4(q3), "Unikitty");
=======
	//Create the quaternions to interpolate
	glm::quat q1 = glm::angleAxis(0.0f, vector3(0.0f, 0.0f, 1.0f));
	quaternion q2 = glm::angleAxis(359.0f, vector3(0.0f, 0.0f, 1.0f)); //if 360 there is a div by 0 somewhere
	quaternion q3;
	
	static float fTimer = 0.0f; //static timer to keep track
	static int clockIndex = m_pSystem->GenClock();//generate a new clock in the system
	fTimer += m_pSystem->LapClock(clockIndex);//get the delta time of that clock

	float fCycleTime = 5.0f;// time the animation will take to perform
	float fPercentage = MapValue(fTimer, 0.0f, fCycleTime, 0.0f, 1.0f); //map the value in a percentage scale

	q3 = glm::mix(q1, q2, fPercentage); //slerp the quaternions
	
	m_pMeshMngr->SetModelMatrix(ToMatrix4(q3), "Cow");//transform the quaternion to a matrix and assign it to the model
<<<<<<< HEAD
>>>>>>> 1f0255ccf433290ba131bbf9af961a9c4ddf110f
=======
>>>>>>> d5b2223fd6ca24b95c3a20b3621f3644606d7093
>>>>>>> 1841ff349f26c4d02d2ed86ad76903613ed91e74
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddSkyboxToRenderList();
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	//printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
<<<<<<< HEAD
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("Selection: ");
	m_pMeshMngr->PrintLine(m_pMeshMngr->GetInstanceGroupName(m_selection.first, m_selection.second), REYELLOW);
=======
	m_pMeshMngr->PrintLine("");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	m_pMeshMngr->Print("Timer: ");
	m_pMeshMngr->PrintLine(std::to_string(fTimer), REYELLOW);
<<<<<<< HEAD
>>>>>>> 1f0255ccf433290ba131bbf9af961a9c4ddf110f
=======
>>>>>>> d5b2223fd6ca24b95c3a20b3621f3644606d7093
>>>>>>> 1841ff349f26c4d02d2ed86ad76903613ed91e74
	
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
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