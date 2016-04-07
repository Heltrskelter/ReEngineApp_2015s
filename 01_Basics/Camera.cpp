#include "Camera.h"

using namespace ReEng;
//Camera Class

Camera::Camera(void)
{
}


Camera::~Camera(void)
{
}

//returns view Matrix
matrix4 Camera::GetView(void) {
	matrix4 view = glm::lookAt(m_v3Position, m_v3Target, m_v3Top);
	return view;
}

//returns Projection matrix
matrix4 Camera::GetProjection(bool bOrtographic) {
	matrix4 projection;
	if (bOrtographic) {
	//is orthographic
		m_nMode = CAMERAMODE::CAMROTHOX;
		projection = glm::ortho(-1.5f * float(aspect), 1.5f*float(aspect), -1.5f, 1.5f, -10.0f, 10.0f);
	}
	else { 
		//is in perspective mode
		m_nMode = CAMERAMODE::CAMPERSP; 
		projection = glm::perspective(glm::radians(m_fFOV), float(aspect), m_Near, m_Far);	
	}
	return projection;
}


//Sets Position of Camera
void Camera::SetPosition(vector3 a_v3Position) {
	m_v3Position = a_v3Position;
}

//Sets Target of Camera
void Camera::SetTarget(vector3 a_v3Target) {
	m_v3Target = a_v3Target;
}

//sets the Up vector of the camera
void Camera::SetUp(vector3 a_v3Up) {
	m_v3Upward = a_v3Up;
}

void Camera::MoveForward(float fIncrement) {
	matrix4 view = GetView();
	vector3 cam_Dir = glm::normalize(view - m_v3Position);
}

void Camera::MoveVertical(float fIncrement) {}

void Camera::MoveSideways(float fIncrement) {}

void Camera::ChangePitch(float fIncrement) {
	m_Pitch += fIncrement;
	if (m_Pitch > 360.0f) { m_Pitch -= 360.0f; }
	else if (m_Pitch < -360.0f) { m_Pitch -= 360.0f; }
}

void Camera::ChangeYaw(float fIncrement) {
	m_Yaw += fIncrement;
	if (m_Yaw > 360.0f) { m_Yaw -= 360.0f; }
	else if (m_Yaw < -360.0f) { m_Yaw -= 360.0f; }
}

void Camera::ChangeRoll(float fIncrement) {
	m_Roll += fIncrement;
	if (m_Roll > 360.0f) { m_Roll -= 360.0f; }
	else if (m_Roll < -360.0f) { m_Roll -= 360.0f; }
}