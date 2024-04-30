#include "Sound.h"

void Frontend_PlaySound(char* name)
{
	static uintptr_t pat = _pattern(PATID_Frontend_PlaySound_Call);
	if (pat)
	{
		static void(__cdecl * funcAddr)(char*) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			funcAddr(name);
	}
}
