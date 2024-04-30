#include "Camera.h"
#include "..\plugin\Menu.h"

Camera* TheCamera;

void Camera::SetPositionHooked(Vector* pos)
{
	TheCamera = this;

	if (TheMenu->m_bCustomCameraFOV)
		SetFOV(TheMenu->camFov);

	if (!TheMenu->m_bCustomCameraPos || TheMenu->fps.enabled)
	{
		if (!TheMenu->m_bCustomCameraPos)
			TheMenu->camPos = *pos;

		if (TheMenu->fps.enabled)
		{
			CharacterObject* plr = GetMainCharacter();
			if (plr)
			{
				Vector fpView = {};
				Matrix viewMatrix = plr->GetMatrix();
				fpView = *plr->GetBonePosition(BONE_HEAD);
				fpView.Y += TheMenu->fps.YAdjust;

				fpView += viewMatrix.GetForward() * TheMenu->fps.ZAdjust;
				fpView += viewMatrix.GetRight() * TheMenu->fps.XAdjust;

				TheMenu->camPos = fpView;
				*pos = fpView;
			}
		}

	}
	else
	{
		*pos = TheMenu->camPos;
	}

	SetPosition(pos);
}

void Camera::SetPosition(Vector* pos)
{
	*(Vector*)(this + 100) = *pos;
	(*(void(__thiscall**)(int, int))(**(int**)(this + 132) + 100))(*(int*)(this + 132), (int)this + 52);

	//static uintptr_t pat = _pattern(PATID_Camera_SetPosition);
	//if (pat)
	//	((void(__thiscall*)(Camera*, Vector*))pat)(this, pos);
}

void Camera::SetFOV(float FOV)
{
	static uintptr_t pat = _pattern(PATID_Camera_SetFOV);
	if (pat)
		((void(__thiscall*)(Camera*, float))pat)(this, FOV);
}

void Camera::UnknownCollision()
{
	static uintptr_t pat = _pattern(PATID_Camera_CollisionFunction);

	// seems to be some collision thing? no idea
	if (TheMenu->m_bFreeCam)
	{
		Matrix* mat = (Matrix*)(this);
		mat->M[3][0] = TheMenu->camPos.X;
		mat->M[3][1] = TheMenu->camPos.Y;
		mat->M[3][2] = TheMenu->camPos.Z;

		Matrix* mat2 = (Matrix*)((int)this + 64);
		mat2->M[3][0] = TheMenu->camPos.X;
		mat2->M[3][1] = TheMenu->camPos.Y;
		mat2->M[3][2] = TheMenu->camPos.Z;
	}
	if (pat)
		((void(__thiscall*)(Camera*))pat)(this);
}
