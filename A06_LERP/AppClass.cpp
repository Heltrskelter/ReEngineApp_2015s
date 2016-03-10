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
	
	 m_pSphere = new PrimitiveClass[11];
	//m4 matrix
	m_pMatirx = new matrix4[11];


	//fill points array
	points[0] = vector3(-4.0f, -2.0f, 5.0f);
	points[1] = vector3(1.0f, -2.0f, 5.0f);
	points[2] = vector3(-3.0f, -1.0f, 3.0f);
	points[3] = vector3(2.0f, -1.0f, 3.0f);
	points[4] = vector3(-2.0f, 0.0f, 0.0f);
	points[5] = vector3(3.0f, 0.0f, 0.0f);
	points[6] = vector3(-1.0f, 1.0f, -3.0f);
	points[7] = vector3(4.0f, 1.0f, -3.0f);
	points[8] = vector3(0.0f, 2.0f, -5.0f);
	points[9] = vector3(5.0f, 2.0f, -5.0f);
	points[10] = vector3(1.0f, 3.0f, -5.0f);

	//create spheres and translate matricies

	for (int s = 0; s < 11; s++) {
		m_pSphere[s].GenerateSphere(0.1f, 5, RERED);
		m_pMatirx[s] = glm::translate(points[s]);
	}
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

	m_pMeshMngr->SetModelMatrix(IDENTITY_M4, "WallEye");
	
	int startPoint = static_cast<int>(fRunTime / fDuration) % 11;
	int endPoint = (startPoint + 1) % 11;

	m_pMeshMngr->PrintLine("start: "+std::to_string( startPoint));
	m_pMeshMngr->PrintLine("end: " + std::to_string(endPoint));

	float fPercent = MapValue(static_cast<float>(fRunTime), 0.0f, static_cast<float>(fDuration), 0.0f, 1.0f);
	fPercent -= static_cast<int>(fPercent);
	m_pMeshMngr->PrintLine("p: " + std::to_string(fPercent));

	m_pMeshMngr->SetModelMatrix(glm::translate(glm::lerp(points[startPoint], points[endPoint], fPercent)), "WallEye");

	

	
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	//spheres
	matrix4 mProjection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 mView = m_pCameraMngr->GetViewMatrix();

	for (uint i = 0; i < 11; i++) {
		m_pSphere[i].Render(mProjection, mView, m_pMatirx[i]);
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	delete m_pSphere;
	delete m_pMatirx;

	super::Release(); //release the memory of the inherited fields
}