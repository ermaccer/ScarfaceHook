#include "Scarface.h"
#include "ScarfaceMenu.h"
void runScript(const char* script)
{
	((void(__cdecl*)(const char*, int, int, int, int))0x4922D0)(script,0,0,0,-1);
}

void Camera::SetPosition(CVector* pos)
{
	if (!TheMenu->freezeCam)
	{
		TheMenu->camPos = *pos;
		((void(__thiscall*)(Camera*, CVector*))0x561640)(this, pos);
	}
	else
		((void(__thiscall*)(Camera*, CVector*))0x561640)(this, &TheMenu->camPos);

}
