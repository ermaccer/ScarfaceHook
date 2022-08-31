#include "Camera.h"
#include "..\plugin\ScarfaceMenu.h"
#include <iostream>
Camera* TheCamera;
void Camera::SetPosition(Vector* pos)
{
	TheCamera = this;
	if (TheMenu->m_bCustomCameraFOV)
		SetFOV(TheMenu->camFov);

	if (!TheMenu->m_bCustomCameraPos || TheMenu->fps.enabled)
	{
		if (!TheMenu->m_bCustomCameraPos)
		{
			TheMenu->camPos = *pos;
			((void(__thiscall*)(Camera*, Vector*))0x561640)(this, pos);
		}

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
				((void(__thiscall*)(Camera*, Vector*))0x561640)(this, &fpView);
			}
		}

	}
	else
	{
		((void(__thiscall*)(Camera*, Vector*))0x561640)(this, &TheMenu->camPos);
	}

}

void Camera::SetFOV(float FOV)
{
	((void(__thiscall*)(Camera*, float))0x5616E0)(this, FOV);
}

void Camera::sub_69EA90(Matrix* data)
{
	// seems to be some collision thing? no idea
	if (TheMenu->m_bFreeCam)
	{
		data->M[3][0] = TheMenu->camPos.X;
		data->M[3][1] = TheMenu->camPos.Y;
		data->M[3][2] = TheMenu->camPos.Z;
	}
	((void(__thiscall*)(Camera*, void*))0x69EA90)(this, data);
}
