
#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{
	//Camera Class
	class ReEngDLL Camera
	{
		CAMERAMODE m_nMode = CAMERAMODE::CAMPERSP; //Sets the mode the camera will display

		float m_fFOV = 45.0f;
		double aspect = 4.0f / 3.0f;
		float m_Near = 0.001f;
		float m_Far = 1000.0f;
		

		vector3 m_v3Position = vector3(0.0f, 0.0f, 5.0f);
		vector3 m_v3Target = vector3(0.0f, 0.0f, 0.0f);
		vector3 m_v3Top = vector3(0.0f, 1.0f, 0.0f);

		vector3 m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
		vector3 m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		vector3 m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);

		float m_Pitch = 0.0f;
		float m_Yaw = 0.0f;
		float m_Roll = 0.0f;

		matrix4 m_m4Projection = matrix4(1.0f);
		matrix4 m_m4View = matrix4(1.0f);

	public:
		
		Camera(void);
		~Camera(void);
		
		matrix4 GetView(void);
		//returns view Matrix

		matrix4 GetProjection(bool bOrtographic);
		//returns Projection matrix

		void SetPosition(vector3 a_v3Position);
		//Sets Position of Camera

		void SetTarget(vector3 a_v3Target);
		//Sets Target of Camera

		void SetUp(vector3 a_v3Up);
		//sets the Up vector of the camera

		void MoveForward(float fIncrement);
		
		void MoveVertical(float fIncrement);
		
		void MoveSideways(float fIncrement);
		
		void ChangePitch(float fIncrement);
		
		void ChangeYaw(float fIncrement);
		
		void ChangeRoll(float fIncrement);
		

	private:
		
		void Release(void);
	};

	EXPIMP_TEMPLATE template class ReEngDLL std::vector<Camera>;
	EXPIMP_TEMPLATE template class ReEngDLL std::vector<Camera*>;
}
#endif //__CAMERACLASS_H_