// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "eDirectX9Hook.h"
#include "eDirectInput8Hook.h"
#include "utils/MemoryMgr.h"
#include <iostream>
#include "scarface/Scarface.h"
#include "plugin/ScarfaceMenu.h"
#include "SettingsMgr.h"
#include "hooks.h"

using namespace Memory::VP;

void ImGuiInputWatcher()
{
	// scroll wheel handled by dinput8 hook
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

HRESULT WINAPI CoCreateInstance_Hook(IID& rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID* ppv)
{
	HRESULT res;
	if (rclsid == CLSID_DirectInput8)
	{
		res = CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv);
		eDirectInput8Hook::SetClassInterface(*(int*)(ppv));
		eDirectInput8Hook::Init();
		return res;

	}
	else
	{
		res = CoCreateInstance(rclsid, pUnkOuter, dwClsContext, riid, ppv);
		return res;
	}
}


void Init()
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);

	TheMenu->Init();
	hooks::Init();

	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ImGuiInputWatcher), nullptr, 0, nullptr);

	InjectHook(0x7035DA, eDirectX9Hook::Direct3DCreate9_Hook);	
	if (!SettingsMgr->bUseAlternateMethodToDisableInput)
	Patch(0x9CE540, CoCreateInstance_Hook);
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		Init();
		eDirectX9Hook::Init("Scarface: The World is Yours");
		if (!SettingsMgr->bUseAlternateMethodToDisableInput)
		eDirectInput8Hook::SetModule(hMod);
		break;
	case DLL_PROCESS_DETACH:
		eDirectX9Hook::Destroy();
		if (!SettingsMgr->bUseAlternateMethodToDisableInput)
		eDirectInput8Hook::Destroy();
		break;
	}
	return TRUE;
}

