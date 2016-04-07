
#ifndef __CAMERA_H_
#define __CAMERA_H_


#include "RE\system\SystemSingleton.h"

namespace ReEng
{
	//Camera Class
	class ReEngDLL Camera
	{
		float m_fFOV = 45.0f;

		vector3 m_v3Position = vector3(0.0f, 0.0f, 5.0f);
		vector3 m_v3Target = vector3(0.0f, 0.0f, 0.0f);
		vector3 m_v3Top = vector3(0.0f, 1.0f, 0.0f);

		vector3 m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
		vector3 m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		vector3 m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);

		vector3 m_v3PitchYawRoll = vector3(0.0f);

		matrix4 m_m4Projection = matrix4(1.0f);
		matrix4 m_m4View = matrix4(1.0f);

	public:
		Camera(void);

		Camera(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);

		Camera(Camera const& other);

		Camera& operator=(Camera const& other);

		~Camera(void);

		matrix4 GetView(void);

		matrix4 GetProjection(bool bOrtographic);


		void SetPosition(vector3 a_v3Position);

		void SetTarget(vector3 a_v3Target);

		void SetUp(vector3 a_v3Upward);
		void MoveForward(float a_fDistance = 0.1f);

		void MoveVertical(float a_fDistance = 0.1f);

		void MoveSideways(float a_fDistance = 0.1f);

		void ChangePitch(float a_fDegree = 0.01f);

		void ChangeYaw(float a_fDegree = 0.01f);

		void ChangeRoll(float a_fDegree = 0.01f);

		void ResetCamera(void);

	private:

		void Release(void);

	};

}

#endif //__CAMERACLASS_H_
