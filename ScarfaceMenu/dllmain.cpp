// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "eDirectX9Hook.h"
#include "utils/MemoryMgr.h"
#include <iostream>

void ImGuiInputWatcher()
{
	while (true)
	{
		if (eDirectX9Hook::ms_bInit)
		{
			ImGuiIO& io = ImGui::GetIO();
			POINT mPos;
			GetCursorPos(&mPos);
			ScreenToClient(eDirectX9Hook::ms_hWindow, &mPos);
			io.MousePos.x = mPos.x;
			io.MousePos.y = mPos.y;
			io.MouseDown[0] = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
			io.MouseDown[1] = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
			io.MouseDown[2] = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;
		}


		Sleep(1);
	}
}

int HookHash(char* input, char a2)
{
	FILE* pFile = fopen("hash_log.txt", "a+");

	int result = ((int(__cdecl*)(const char*))0x498A90)(input);

	if (!result)
	{
		if (a2)
			result = ((int(__cdecl*)(const char*, int))0x6DC1E0)(input,0);
		else
			result = ((int(__cdecl*)(const char*, int))0x6DC190)(input,0);
	}

	fprintf(pFile, "%s |\t %s\n", input, ((char*(__cdecl*)(int))0x498A00)(result));
	fclose(pFile);

	return result; 
}



BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		Memory::VP::InjectHook(0x498B10, HookHash, PATCH_JUMP);
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ImGuiInputWatcher), nullptr, 0, nullptr);
		CreateThread(nullptr, 0, DirectXHookThread, hMod, 0, nullptr);

		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}

