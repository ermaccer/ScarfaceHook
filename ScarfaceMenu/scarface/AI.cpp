#include "AI.h"

int AICommandSequencer::RegisterAction(const char* name)
{
	return ((int(__thiscall*)(AICommandSequencer*, const char*))0x541C30)(this, name);
}

void AICommandSequencer::Wait(int unk, float time)
{
	((void(__thiscall*)(AICommandSequencer*, float))0x53F810)(this, time);

}

void AICommandSequencer::PlayAnim(const char* name, int flag, int loop)
{
	((void(__thiscall*)(AICommandSequencer*, const char*, int, int))0x53D890)(this, name, flag, loop);
}

void AICommandSequencer::RunAction()
{
	((void(__thiscall*)(AICommandSequencer*))0x53D2A0)(this);
	((void(__thiscall*)(AICommandSequencer*))0x541CD0)(this);
}
