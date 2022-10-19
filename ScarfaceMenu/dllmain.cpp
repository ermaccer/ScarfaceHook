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
#include "VersionCheck.h"

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

HRESULT __stdcall CoCreateInstanceProxy(LPCTSTR szDllName,REFCLSID rclsid, IUnknown* pUnkOuter, REFIID riid, LPVOID FAR* ppv)
{
	HRESULT hr = REGDB_E_KEYMISSING;

	HMODULE hDll = ::LoadLibrary(szDllName);
	if (hDll == 0)
		return hr;

	typedef HRESULT(__stdcall* pDllGetClassObject)(REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv);
	pDllGetClassObject GetClassObject = (pDllGetClassObject)::GetProcAddress(hDll, "DllGetClassObject");
	if (GetClassObject == 0)
	{
		::FreeLibrary(hDll);
		return hr;
	}

	IClassFactory* pIFactory;

	hr = GetClassObject(rclsid, IID_IClassFactory, (LPVOID*)&pIFactory);

	if (!SUCCEEDED(hr))
		return hr;

	hr = pIFactory->CreateInstance(pUnkOuter, riid, ppv);
	pIFactory->Release();

	return hr;
}

HRESULT WINAPI CoCreateInstance_Hook(IID& rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext, REFIID riid, LPVOID* ppv)
{
	HRESULT res;
	if (rclsid == CLSID_DirectInput8)
	{
		res = CoCreateInstanceProxy("dinput8.dll", rclsid, pUnkOuter, riid, ppv);
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

	eDirectX9Hook::RegisterHook(0x64B1CA, 0x64B1D3, Method_EndScene);
	eDirectX9Hook::RegisterHook(0x654922, 0x65492B, Method_Reset);

	if (!SettingsMgr->bUseAlternateMethodToDisableInput)
		Patch(0x9CE540, CoCreateInstance_Hook);
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		if (IsExecutableSpecifiedVersion())
		{
			Init();
			eDirectX9Hook::Init();
			if (!SettingsMgr->bUseAlternateMethodToDisableInput)
				eDirectInput8Hook::SetModule(hMod);
		}
		else
		{
			MessageBoxA(0, "Invalid game version!\nScarfaceHook only supports version 1.0.0.2 of the executable.\n\nIt is highly recommended to find a no-cd executable of 1.0.0.2 for best experience.\n\nThe game will now run without changes.", 0, MB_ICONINFORMATION);
		}
		break;
	case DLL_PROCESS_DETACH:
		if (IsExecutableSpecifiedVersion())
		{
			if (!SettingsMgr->bUseAlternateMethodToDisableInput)
				eDirectInput8Hook::Destroy();
		}
		break;
	}
	return TRUE;
}

