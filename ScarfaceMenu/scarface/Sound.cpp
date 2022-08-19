#include "Sound.h"

void Frontend_PlaySound(char* name)
{
	((void(__cdecl*)(char*))0x4A44D0)(name);
}
