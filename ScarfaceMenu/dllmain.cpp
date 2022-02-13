// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <uti>

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		// a rather weird way to check version but it works, right?
		if (*(int*)0x4884AB == 0x009550E8)
		{
			Memory::VP::Patch<char>(0x7EC9C4, 0);		// 1.0
			Memory::VP::Patch<char>(0x7EC9C5, 0);
		}
		else
		{
			Memory::VP::Patch<char>(0x7C1C54, 0);		// 1.0.2
			Memory::VP::Patch<char>(0x7C1C55, 0);
		}

	}
}