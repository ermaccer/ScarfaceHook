#include "Scarface.h"
#include <iostream>
#include <Windows.h>

void runScript(const char* script)
{
	static uintptr_t pat = _pattern(PATID_runScript_Call);
	if (pat)
	{
		static void (__cdecl * funcAddr)(const char*, int, int, int, int) = nullptr;

		if (!funcAddr)
			ReadCall(pat, funcAddr);

		if (funcAddr)
			funcAddr(script, 0, 0, 0, -1);
	}
}

