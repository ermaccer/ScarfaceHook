#include "Scarface.h"

void runScript(const char* script)
{
	((void(__cdecl*)(const char*, int, int, int, int))0x4922D0)(script,0,0,0,-1);
}
