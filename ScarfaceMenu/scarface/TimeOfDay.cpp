#include "TimeOfDay.h"

void TODObject::SetTime(int hour, int minute)
{
	static uintptr_t pat = _pattern(PATID_TODObject_SetTime_Call);
	if (pat)
	{
		static void(__thiscall * funcAddr)(TODObject*, int, int, int) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			return funcAddr(this, hour, minute, 0);
	}
}

void TODObject::EnableRain(bool status)
{
	static uintptr_t pat = _pattern(PATID_TODObject_EnableRain_Call);
	if (pat)
	{
		static void(__cdecl * funcAddr)(bool) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			return funcAddr(status);
	}
}

TODObject* GetTODObject()
{
	static TODObject* pTODObject = nullptr;

	if (pTODObject == nullptr)
	{
		static uintptr_t pat = _pattern(PATID_TODObject_Instance);
		if (pat)
		{
			unsigned int offset = *(unsigned int*)(pat);
			pTODObject = *(TODObject**)(offset);
		}
	}
	return pTODObject;
}
